/*
 * Copyright (c) 2012-2013 Open Source Community - <http://www.peerfact.org>
 * Copyright (c) 2011-2012 University of Paderborn - UPB
 * Copyright (c) 2005-2011 KOM - Multimedia Communications Lab
 *
 * This file is part of PeerfactSim.KOM.
 *
 * PeerfactSim.KOM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * PeerfactSim.KOM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PeerfactSim.KOM.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// ported to C++ with appropriate modifications for Marlin Protocol

#include <algorithm>
#include <limits>

#include "Subnet.h"
#include "Bandwidth.h"
#include "BandwidthModels/TransferProgress.h"
#include "BandwidthModels/gnp/AbstractGnpNetBandwidthManager.h"
#include "BandwidthModels/gnp/GnpNetBandwidthAllocation.h"
#include "BandwidthModels/gnp/GnpNetBandwidthManager.h"
#include "LatencyModels/GnpLatencyModel.h"
#include "NetworkLayer/IPv4Message.h"
#include "NetworkLayer/NetworkMessage.h"
#include "NetworkLayer/NetworkLayer.h"
#include "TransportLayer/L4Message.h"
#include "TransportLayer/L4Protocol.h"
#include "../EventManagement/Event/EventTypes/MessageToNodeEvent.h"
#include "../Network/Messages/Message.h"
#include "../Network/Messages/SubnetMessage.h"
#include "../Network/Network.h"
#include "../Network/Node/Node.h"

Subnet::Subnet(Network& _network) : network(_network), lastMsgId(0), latencyModel(std::make_shared<GnpLatencyModel>(_network)),
									nextRescheduleTime(0), bandwidthManager(std::make_shared<GnpNetBandwidthManager>(_network)) {}

Subnet::Subnet(Network& _network, std::shared_ptr<GnpLatencyModel> _latencyModel)
	   : network(_network), lastMsgId(0), latencyModel(_latencyModel), nextRescheduleTime(0),
		 bandwidthManager(std::make_shared<GnpNetBandwidthManager>(_network)) {}

std::shared_ptr<AbstractGnpNetBandwidthManager> Subnet::getBandwidthManager() {
	return bandwidthManager;
}

std::shared_ptr<GnpLatencyModel> Subnet::getLatencyModel() {
	return latencyModel;
}

bool Subnet::shouldDropMsg(NodeId senderId, NodeId receiverId, std::shared_ptr<NetworkMessage> msg) {
	double packetLossProbability = latencyModel->getUDPErrorProbability(senderId, receiverId, std::static_pointer_cast<IPv4Message>(msg));

	double randomNum = network.getRandomDouble();

	if(randomNum < packetLossProbability) {
		return true;
	}

	return false;
}

uint64_t Subnet::setMessageId(std::shared_ptr<NetworkMessage> msg) {
	int msgId = msg->getPayload()->getMessageId();

	if(msgId == -1) {
		msgId = lastMsgId++;
		msg->getPayload()->setMessageId(msgId);
	}

	return msgId;
}

void Subnet::send(std::shared_ptr<NetworkMessage> msg, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	NodeId senderId = msg->getSender();
	NodeId receiverId = msg->getReceiver();
	L4ProtocolType l4Protocol = msg->getPayload()->getL4Protocol()->getL4ProtocolType();

	if(senderId == receiverId) {
		return;
	}

	if(l4Protocol == L4ProtocolType::UDP) {
		if(shouldDropMsg(senderId, receiverId, msg)) {
			return;
		}
	}

	int msgId = setMessageId(msg);

	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	if(msg->getNumFragments() == 1) {
		uint64_t propagationTicks = latencyModel->getPropagationDelay(senderId, receiverId);
		uint64_t transmissionTicks = latencyModel->getTransmissionDelay(msg->getSize(), std::min(sender->getNetworkLayer()->getMaxBandwidth()->getUpBW(),
																								receiver->getNetworkLayer()->getMaxBandwidth()->getDownBW()));
		uint64_t transmissionEndTick = std::max(_currentTick, sender->getNetworkLayer()->getNextFreeSendingTick()) + transmissionTicks;
		sender->getNetworkLayer()->setNextFreeSendingTick(transmissionEndTick);

		uint64_t ticksBeforeReception = (sender->getNetworkLayer()->getNextFreeSendingTick() > _currentTick
											? sender->getNetworkLayer()->getNextFreeSendingTick() - _currentTick
											: 0)
										+ transmissionTicks + propagationTicks;

		std::shared_ptr<TransferProgress> transferProgress(new TransferProgress(msg, 0, std::numeric_limits<std::size_t>::max(), _currentTick));

		_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
			MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::MESSAGE_RECVD, transferProgress)),
							   -1, -1, ticksBeforeReception)
		));
	}
	else {
//		std::cout<<"a1"<<std::endl;
		double maxBandwidthRequired = sender->getNetworkLayer()->getMaxBandwidth()->getUpBW();
		if(l4Protocol == L4ProtocolType::TCP) {
//			std::cout<<"a2"<<std::endl;
			double tcpThroughput = latencyModel->getTCPThroughput(senderId, receiverId, false);
			maxBandwidthRequired = std::min(maxBandwidthRequired, tcpThroughput);
		}
		std::shared_ptr<GnpNetBandwidthAllocation> ba = bandwidthManager->addConnection(senderId, receiverId, maxBandwidthRequired);
		std::shared_ptr<TransferProgress> transferProgress(new TransferProgress(msg, msg->getSize(), 0, _currentTick));
		connectionsToTransfersMap[ba].insert(transferProgress);
		messageIdsToTransfersMap[msgId] = transferProgress;
//		std::cout<<"a3"<<std::endl;
		if(nextRescheduleTime < _currentTick + 1) {
//			std::cout<<"a4"<<std::endl;
			nextRescheduleTime = _currentTick + 1;
			_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
				MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::BANDWIDTH_REALLOC)),
								   -1, -1, 1)
			));
		}
	}
}

void Subnet::cancelTransmission(int _msgId, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::shared_ptr<TransferProgress> tp = messageIdsToTransfersMap[_msgId];
	std::shared_ptr<NetworkMessage> msg = tp->getMessage();
	NodeId senderId = msg->getSender();
	NodeId receiverId = msg->getReceiver();
	std::shared_ptr<Node> sender = network.getNode(senderId);

	double maxBandwidthRequired = sender->getNetworkLayer()->getMaxBandwidth()->getUpBW();

	if(msg->getPayload()->getL4Protocol()->getL4ProtocolType() == L4ProtocolType::TCP) {
		double tcpThroughput = latencyModel->getTCPThroughput(senderId, receiverId, false);
		maxBandwidthRequired = std::min(maxBandwidthRequired, tcpThroughput);
	}

	bandwidthManager->removeConnection(senderId, receiverId, maxBandwidthRequired);

	messageIdsToTransfersMap.erase(_msgId);
	cancelledTransfers.insert(tp);

	if(nextRescheduleTime < _currentTick + 1) {
		nextRescheduleTime = _currentTick + 1;
		_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
			MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::BANDWIDTH_REALLOC)),
							   -1, -1, 1)
		));
	}
}

void Subnet::onDisconnect(NodeId _nodeId, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::shared_ptr<Node> node = network.getNode(_nodeId);
	node->getNetworkLayer()->setOnline(false);

	for(auto ba: bandwidthManager->removeConnections(_nodeId)) {
		std::set<std::shared_ptr<TransferProgress>> transfers = connectionsToTransfersMap[ba];
		connectionsToTransfersMap.erase(ba);
		cancelledTransfers.insert(transfers.begin(), transfers.end());
		if(!transfers.empty()) {
			for(auto tp: transfers) {
				messageIdsToTransfersMap.erase(tp->getMessage()->getPayload()->getMessageId());
			}
		}
		if(nextRescheduleTime < _currentTick + 1) {
			nextRescheduleTime = _currentTick + 1;
			_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
				MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::BANDWIDTH_REALLOC)),
								   -1, -1, 1)
			));
		}
	}
}

void Subnet::forwardToReceiverNetworkLayer(std::shared_ptr<NetworkMessage> msg, std::shared_ptr<Node> sender, std::shared_ptr<Node> receiver) {
	std::cout<<"MESSAGE_FINALLY_RECEIVED by nodeId "<<receiver->getNodeId()<<std::endl;
	if(receiver->getNetworkLayer()->isOnline() &&
			(receiver->getNetworkLayer()->getPartitionGroupId() == sender->getNetworkLayer()->getPartitionGroupId())) {
		receiver->getNetworkLayer()->receive(msg);
	}
}

void Subnet::addToReceiverQueue(std::shared_ptr<NetworkMessage> _message, std::shared_ptr<Node> _sender, std::shared_ptr<Node> _receiver,
								uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	uint64_t transmissionTicks = latencyModel->getTransmissionDelay(_message->getSize(), _receiver->getMaxBandwidth()->getDownBW());
	uint64_t arrivalTick = _receiver->getNetworkLayer()->getNextFreeReceivingTick() + transmissionTicks;
	if(arrivalTick < _currentTick) {
		_receiver->getNetworkLayer()->setNextFreeReceivingTick(_currentTick);
		forwardToReceiverNetworkLayer(_message, _sender, _receiver);
	}
	else {
		_receiver->getNetworkLayer()->setNextFreeReceivingTick(arrivalTick);
		uint64_t ticksBeforeReception = arrivalTick - _currentTick;
		_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
				MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::FWD_TO_RECEIVER, _message)),
								   -1, -1, ticksBeforeReception)
		));
	}
}

void Subnet::onMessageReceived(std::shared_ptr<TransferProgress> _tp, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::shared_ptr<NetworkMessage> msg = _tp->getMessage();
	NodeId senderId = msg->getSender();
	NodeId receiverId = msg->getReceiver();
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);
	if(msg->getNumFragments() == 1) {
		addToReceiverQueue(msg, sender, receiver, _currentTick, _newEvents);
	}
	else {
		if(_tp->isObsolete() || (cancelledTransfers.find(_tp) != cancelledTransfers.end())) {
			cancelledTransfers.erase(_tp);
			std::cout<<"*obsolete* "<<_currentTick<<std::endl;
			return;
		}
		else {
			forwardToReceiverNetworkLayer(msg, sender, receiver);
			if(nextRescheduleTime < _currentTick + 1) {
				nextRescheduleTime = _currentTick + 1;
				_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
					MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::BANDWIDTH_REALLOC)), -1, -1, 1)
				));
			}
		}
		std::cout<<"currentTick: "<<_currentTick<<std::endl;
		double maxBandwidthRequired = sender->getNetworkLayer()->getMaxBandwidth()->getUpBW();
		L4ProtocolType l4Protocol = msg->getPayload()->getL4Protocol()->getL4ProtocolType();
		if(l4Protocol == L4ProtocolType::TCP) {
			double tcpThroughput = latencyModel->getTCPThroughput(senderId, receiverId, false);
			maxBandwidthRequired = std::min(maxBandwidthRequired, tcpThroughput);
		}

		std::shared_ptr<GnpNetBandwidthAllocation> ba = bandwidthManager->removeConnection(senderId, receiverId, maxBandwidthRequired);

		if(connectionsToTransfersMap.find(ba) != connectionsToTransfersMap.end()) {
			if(connectionsToTransfersMap[ba].size() <= 1) {
				connectionsToTransfersMap.erase(ba);
			}
			else {
				connectionsToTransfersMap[ba].erase(_tp);
			}
		}

		messageIdsToTransfersMap.erase(msg->getPayload()->getMessageId());
	}
}

void Subnet::onBandwidthReallocation(uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::cout<<"Subnet::onBandwidthReallocation: "<<_currentTick<<std::endl;
	bandwidthManager->allocateBandwidth();
	for(auto ba: bandwidthManager->getChangedAllocations()) {
		rescheduleTransfers(ba, _currentTick, _newEvents);
	}
}

void Subnet::rescheduleTransfers(std::shared_ptr<GnpNetBandwidthAllocation> _ba, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::cout<<"Subnet::rescheduleTransfers: "<<_currentTick<<std::endl;

	std::set<std::shared_ptr<TransferProgress>> transfers = connectionsToTransfersMap[_ba];
	if(transfers.empty()) return;
	std::set<std::shared_ptr<TransferProgress>> updatedTransfers;

	NodeId senderId = _ba->getSender();
	NodeId receiverId = _ba->getReceiver();
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	double remainingBandwidth = _ba->getAllocatedBandwidth();
	int remainingTransfers = transfers.size();

	for(std::shared_ptr<TransferProgress> tp: transfers) {
		double remainingBytes = tp->getRemainingBytes(_currentTick);
		double bandwidth = remainingBandwidth/remainingTransfers;

//		std::cout<<"transfers/remainingBytes: "<<remainingBytes<<std::endl;
//		std::cout<<"transfers/bandwidth: "<<bandwidth<<std::endl;

		std::shared_ptr<NetworkMessage> msg = tp->getMessage();

		if(msg->getPayload()->getL4Protocol()->getL4ProtocolType() == L4ProtocolType::TCP) {
			double tcpThroughput = latencyModel->getTCPThroughput(senderId, receiverId, false);
			bandwidth = std::min(bandwidth, tcpThroughput);
		}

		remainingBandwidth -= bandwidth;
		remainingTransfers--;

		uint64_t propagationTicks = latencyModel->getPropagationDelay(senderId, receiverId);
		uint64_t transmissionTicks = latencyModel->getTransmissionDelay(remainingBytes, bandwidth);
		uint64_t ticksBeforeReception = transmissionTicks + propagationTicks;

		std::shared_ptr<TransferProgress> transferProgress(new TransferProgress(msg, remainingBytes, bandwidth, _currentTick));

		_newEvents.push_back(std::make_shared<MessageToNodeEvent>(
			MessageToNodeEvent(std::shared_ptr<Message>(new SubnetMessage(SubnetMessageType::MESSAGE_RECVD, transferProgress)),
							   -1, -1, ticksBeforeReception)
		));

		updatedTransfers.insert(transferProgress);

		int msgId = msg->getPayload()->getMessageId();
		messageIdsToTransfersMap[msgId] = transferProgress;

		transferProgress->setFirstSchedule(false);
		if(!tp->isFirstSchedule()) {
			tp->setObsolete(true);
		}
	}

	connectionsToTransfersMap[_ba] = updatedTransfers;
}

void Subnet::onSubnetMessage(std::shared_ptr<SubnetMessage> msg, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	switch(msg->getSubnetType()) {
		case SubnetMessageType::MESSAGE_RECVD: {
			std::cout<<"MESSAGE_RECVD: "<<_currentTick<<std::endl;
			onMessageReceived(msg->getTransferProgress(), _currentTick, _newEvents);
			break;
		}
		case SubnetMessageType::FWD_TO_RECEIVER: {
			std::cout<<"FWD_TO_RECEIVER"<<std::endl;
			break;
		}
		case SubnetMessageType::BANDWIDTH_REALLOC: {
			std::cout<<"BANDWIDTH_REALLOC"<<std::endl;
			onBandwidthReallocation(_currentTick, _newEvents);
			break;
		}
		case SubnetMessageType::DISCONNECT: {
			std::cout<<"DISCONNECT node #"<<msg->getNetworkMessage()->getReceiver()<<std::endl;
			onDisconnect(msg->getNetworkMessage()->getReceiver(), _currentTick, _newEvents);
			break;
		}
		case SubnetMessageType::RECONNECT: {
			break;
		}
		case SubnetMessageType::CANCEL_TRANSMISSION: {
			cancelTransmission(msg->getNetworkMessage()->getPayload()->getMessageId(), _currentTick, _newEvents);
			break;
		}
	}
}
