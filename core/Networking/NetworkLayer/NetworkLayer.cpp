#include "NetworkLayer.h"
#include "IPv4Message.h"
#include "NetworkMessage.h"
#include "../Bandwidth.h"
#include "../LatencyModels/GnpLatencyModel.h"
#include "../Subnet.h"
#include "../TransportLayer/TCPMessage.h"
#include "../../EventManagement/Event/EventTypes/MessageToNodeEvent.h"

#include "../TransportLayer/L4Message.h"

NetworkLayer::NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet, NodeId _myNodeId) :
	online(true), partitionGroupId(-1), subnet(_subnet), nextFreeReceivingTick(0), nextFreeSendingTick(0), myL3Address(_myNodeId),
	currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))),
	maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))) {}

bool NetworkLayer::isOnline() {
	return online;
}

L3Address NetworkLayer::getL3Address() {
	return myL3Address;
}

int NetworkLayer::getPartitionGroupId() const {
	return partitionGroupId;
}

void NetworkLayer::setPartitionGroupId(int _partitionGroupId) {
	partitionGroupId = _partitionGroupId;
}

std::shared_ptr<Bandwidth> NetworkLayer::getCurrentBandwidth() {
	return currentBandwidth;
}

std::shared_ptr<Bandwidth> NetworkLayer::getMaxBandwidth() {
	return maxBandwidth;
}

uint64_t NetworkLayer::getNextFreeReceivingTick() const {
	return nextFreeReceivingTick;
}

void NetworkLayer::setNextFreeReceivingTick(uint64_t _nextFreeReceivingTime) {
	nextFreeReceivingTick = _nextFreeReceivingTime;
}

uint64_t NetworkLayer::getNextFreeSendingTick() const {
	return nextFreeSendingTick;
}

void NetworkLayer::setNextFreeSendingTick(uint64_t _nextFreeSendingTime) {
	nextFreeSendingTick = _nextFreeSendingTime;
}

void NetworkLayer::send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<TCPMessage> _payload,
						uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents) {
	if(online) {
		std::shared_ptr<IPv4Message> msg(std::make_shared<IPv4Message>(myL3Address.nodeId, _dest.nodeId, _payload));
		std::shared_ptr<NetworkMessage> networkMsg = std::static_pointer_cast<NetworkMessage>(msg);
		subnet->send(networkMsg, _currentTick, _newEvents);
	}
	else {
	}
}

void NetworkLayer::receive(std::shared_ptr<NetworkMessage> _message) {
	std::cout<<"NetworkLayer::receive"<<std::endl;
	std::cout<<"sender: "<<_message->getSender()<<std::endl;
	std::cout<<"receiver: "<<_message->getReceiver()<<std::endl;
	std::cout<<"type: "<<_message->getPayload()->getPayload()->getType()<<std::endl;
}

std::shared_ptr<Subnet> NetworkLayer::getSubnet() {
	return subnet;
}
