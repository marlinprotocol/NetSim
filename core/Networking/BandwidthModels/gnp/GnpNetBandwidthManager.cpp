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

/**
 *
 * original author Gerald Klunker <peerfact@kom.tu-darmstadt.de>
 * @version 0.01, 07/12/12
 * ported to C++ for Marlin Protocol
 */

#include <algorithm>
#include <limits>

#include "GnpNetBandwidthManager.h"
#include "GnpNetBandwidthAllocation.h"
#include "../../Bandwidth.h"
#include "../../../Network/Network.h"

//test
#include <iostream>
//end test

GnpNetBandwidthManager::GnpNetBandwidthManager(Network& _network) : AbstractGnpNetBandwidthManager(_network) {}

void GnpNetBandwidthManager::allocateBandwidth() {
	changedAllocations.clear();

	// Initialize Bids and Allocations
	tempConnections.clear();
	tempSenderConnections.clear(); // TODO: is it needed? its there at the end of the fn as well
	tempReceiverConnections.clear(); // TODO: is it needed? its there at the end of the fn as well

	std::set<NodeId> senders, receivers;

	for (auto it: connectionsSenderToReceiver) {
		for(auto it2: connectionsSenderToReceiver[it.first]) {
			tempSenderConnections[it.first].insert(it2.second);
			tempConnections.insert(it2.second);
			senders.insert(it.first);
//			std::cout<<"sender: "<<network.getNode(it.first)->getCurrentBandwidth()->getUpBW()<<std::endl;
		}
	}

	for (auto it: connectionsReceiverToSender) {
		for(auto it2: connectionsReceiverToSender[it.first]) {
			tempReceiverConnections[it.first].insert(it2.second);
			receivers.insert(it.first);
//			std::cout<<"receiver: "<<it.first<<std::endl;
		}
	}

	for(auto s: senders) {
		auto senderCurrentBandwidth = network.getNode(s)->getCurrentBandwidth();
		auto senderMaxBandwidth = network.getNode(s)->getMaxBandwidth();
		senderCurrentBandwidth->resetBandwidth(senderCurrentBandwidth->getDownBW(), senderMaxBandwidth->getUpBW());
	}

	for(auto r: receivers) {
		auto receiverCurrentBandwidth = network.getNode(r)->getCurrentBandwidth();
		auto receiverMaxBandwidth = network.getNode(r)->getMaxBandwidth();
		receiverCurrentBandwidth->resetBandwidth(receiverMaxBandwidth->getDownBW(), receiverCurrentBandwidth->getUpBW());
	}

	for (std::shared_ptr<GnpNetBandwidthAllocation> c: tempConnections) {
		c->initConnection();
	}

	std::set<NodeId> deleteSenders, deleteReceivers;
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> deleteConnections;
	while (!tempConnections.empty()) {
		for(auto s: senders) {
//			std::cout<<"getCurrentBandwidth()->getUpBW(): "<<network.getNode(s)->getCurrentBandwidth()->getUpBW()<<std::endl;
			generateMeanBids(network.getNode(s)->getCurrentBandwidth()->getUpBW(),
							 tempSenderConnections[s], true);
		}

		for(auto r: receivers) {
//			std::cout<<"getCurrentBandwidth()->getDownBW(): "<<network.getNode(r)->getCurrentBandwidth()->getDownBW()<<std::endl;
			generateMeanBids(network.getNode(r)->getCurrentBandwidth()->getDownBW(),
							 tempReceiverConnections[r], false);
		}

		step++;

		for(auto s: senders) {
			if(generateMinimumBids(s, true)) {
				deleteSenders.insert(s);
			}
		}

		for(auto r: receivers) {
			if(generateMinimumBids(r, false)) {
				deleteReceivers.insert(r);
			}
		}

		for (std::shared_ptr<GnpNetBandwidthAllocation> c: tempConnections) {
			if(assignAllocation(c)) {
				deleteConnections.insert(c);
			}
		}

		for(auto it: deleteSenders) {
			senders.erase(it);
		}

		for(auto it: deleteReceivers) {
			receivers.erase(it);
		}

		for(auto it: deleteConnections) {
			tempConnections.erase(it);
		}

		for (std::shared_ptr<GnpNetBandwidthAllocation> c: deleteConnections) {
			NodeId sender = c->getSender();
			NodeId receiver = c->getReceiver();
			if (tempSenderConnections.find(sender) != tempSenderConnections.end()) {
				tempSenderConnections[sender].erase(c);
			}
			if (tempReceiverConnections.find(receiver) != tempReceiverConnections.end()) {
				tempReceiverConnections[receiver].erase(c);
			}
		}

		deleteSenders.clear();
		deleteReceivers.clear();
		deleteConnections.clear();
	}
//	std::cout<<"getAllocatedBandwidthInside: "<<getBandwidthAllocation(0, 3)->getAllocatedBandwidth()<<std::endl;
	step = 0;
	tempConnections.clear();
	tempSenderConnections.clear();
	tempReceiverConnections.clear();
}

int GnpNetBandwidthManager::generateMeanBids(double bandwidth,
											 std::set<std::shared_ptr<GnpNetBandwidthAllocation>> unassigned,
											 bool isSender) {
	if (unassigned.empty()) {
		return 0;
	}

	// find connections with an upper bound of throughput that is below fair
	// fraction of bandwidth
	double minBW = std::numeric_limits<double>::max();
	double share = bandwidth / unassigned.size();
	std::shared_ptr<GnpNetBandwidthAllocation> min = nullptr;
	for(auto ba: unassigned) {
		double bw = 0;
		bw = std::min(share, ba->getBandwidthNeeds());
		if (bw < minBW) {
			minBW = bw;
			min = ba;
		}
	}

	if (minBW < share) {
		min->setBid(minBW, false, isSender, step);
		unassigned.erase(min);
		double newBandwidth = bandwidth - minBW;
		int counter = generateMeanBids(newBandwidth, unassigned, isSender);
		if (minBW > min->getPreviousBid(!isSender, step)) {
			return counter + 1;
		}
		else {
			return counter;
		}
	}
	else {
		int counter = 0;
		for (std::shared_ptr<GnpNetBandwidthAllocation> ba : unassigned) {
			ba->setBid(share, false, isSender, step);
			if (share > ba->getPreviousBid(!isSender, step)) {
				counter++;
			}
		}
		return counter;
	}
}

bool GnpNetBandwidthManager::generateMinimumBids(NodeId p, bool sender) {
	// get unassigned connections related to p
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> connections =
			sender ? tempSenderConnections[p] : tempReceiverConnections[p];

	// if one connection left repeat bid and set as minimum
	if (connections.size() == 1) {
		std::shared_ptr<GnpNetBandwidthAllocation> c = *(connections.begin());
		c->setBid(c->getPreviousBid(sender, step), true, sender, step);
		return true;
	}

	// Fair Share bandwidth
	double bandwidth = sender ? network.getNode(p)->getCurrentBandwidth()->getUpBW()
							  : network.getNode(p)->getCurrentBandwidth()->getDownBW();

	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> temp;
	temp.insert(connections.begin(), connections.end());

	int smallerBids = generateMeanBids(bandwidth, temp, sender);

	// no opposite Bid is smaller than own bid
	// mark as minimum Bid
	if (smallerBids == 0) {
		for (auto c : connections) {
			c->setBid(c->getCurrentBid(sender, step), true, sender, step);
		}
		return true;
	}
	// some opposite Bids are smaller than own bid:
	else {
		// get Connections with slowest Bids
		std::set<std::shared_ptr<GnpNetBandwidthAllocation>> slowestConnections;
		double slowestBid = std::numeric_limits<double>::max();
		for (std::shared_ptr<GnpNetBandwidthAllocation> c: connections) {
			double currentBid = c->getPreviousBid(!sender, step);
			if (currentBid < slowestBid) {
				slowestBid = currentBid;
			}
		}
		for (auto c: connections) {
			double currentBid = c->getPreviousBid(!sender, step);
			if (currentBid == slowestBid) {
				slowestConnections.insert(c);
			}
		}

		// double bandwidth = (sender) ? p.getCurrentUploadBandwidth() :
		// p.getCurrentDownloadBandwidth();
		double min = (*(slowestConnections.begin()))->getPreviousBid(!sender, step);
		for (auto c: slowestConnections) {
			c->setBid(min, true, sender, step);
			bandwidth -= min;
		}

		std::set<std::shared_ptr<GnpNetBandwidthAllocation>> fasterConnections;
		fasterConnections.insert(connections.begin(), connections.end());

		for(auto it: slowestConnections) {
			fasterConnections.erase(it);
		}

		generateMeanBids(bandwidth, fasterConnections, sender);
		return false;
	}
}

bool GnpNetBandwidthManager::assignAllocation(std::shared_ptr<GnpNetBandwidthAllocation> c) {
	double bidSender = c->getCurrentBid(true, step);
	double bidReceiver = c->getCurrentBid(false, step);

	if (bidSender <= bidReceiver && c->isMinBid(true) && c->isBidRepeated(true)) {
		if (bidSender != c->getAllocatedBandwidth()) {
			changedAllocations.insert(c);
		}
		c->setAllocatedBandwidth(bidSender);
//std::cout<<"setAllocatedBandwidth1: "<<bidSender<<std::endl;

		auto sender = network.getNode(c->getSender());
		auto receiver = network.getNode(c->getReceiver());

//		std::cout<<"sender-receiver1: "<<sender->getNodeId()<<" "<<receiver->getNodeId()<<std::endl;
//		std::cout<<"sender->getCurrentBandwidth(): "
//				 <<sender->getCurrentBandwidth()->getDownBW()
//				 <<" "<<sender->getCurrentBandwidth()->getUpBW() - bidSender<<std::endl;
//		std::cout<<"sender->getCurrentBandwidth()->getUpBW(): "
//				 <<sender->getCurrentBandwidth()->getUpBW()
//				 <<", bidSender: "<<bidSender<<std::endl;
//		std::cout<<"receiver->getCurrentBandwidth(): "
//						 <<receiver->getCurrentBandwidth()->getDownBW() - bidSender
//						 <<" "<<receiver->getCurrentBandwidth()->getUpBW()<<std::endl;
//		std::cout<<"----"<<std::endl;

		// set the sender's up bw to the subtraction of its current up bw and bidSender
		sender->getCurrentBandwidth()->resetBandwidth(sender->getCurrentBandwidth()->getDownBW(),
													  sender->getCurrentBandwidth()->getUpBW() - bidSender);

		// set the receiver's down bw to the subtraction of its current down bw and bidSender
		receiver->getCurrentBandwidth()->resetBandwidth(receiver->getCurrentBandwidth()->getDownBW() - bidSender,
														receiver->getCurrentBandwidth()->getUpBW());

		return true;
	}
	else if (bidSender >= bidReceiver && c->isMinBid(false) && c->isBidRepeated(false)) {
		if (bidReceiver != c->getAllocatedBandwidth()) {
			changedAllocations.insert(c);
		}
		c->setAllocatedBandwidth(bidReceiver);
//		std::cout<<"setAllocatedBandwidth2: "<<bidReceiver<<std::endl;

		auto sender = network.getNode(c->getSender());
		auto receiver = network.getNode(c->getReceiver());

//		std::cout<<"sender-receiver2: "<<sender->getNodeId()<<" "<<receiver->getNodeId()<<std::endl;
//		std::cout<<"sender->getCurrentBandwidth(): "
//				 <<sender->getCurrentBandwidth()->getDownBW()
//				 <<" "<<sender->getCurrentBandwidth()->getUpBW() - bidReceiver<<std::endl;
//		std::cout<<"receiver->getCurrentBandwidth(): "
//						 <<receiver->getCurrentBandwidth()->getDownBW() - bidReceiver
//						 <<" "<<receiver->getCurrentBandwidth()->getUpBW()<<std::endl;
//		std::cout<<"----"<<std::endl;

		// analog to the other case with bidReceiver
		sender->getCurrentBandwidth()->resetBandwidth(sender->getCurrentBandwidth()->getDownBW(),
													  sender->getCurrentBandwidth()->getUpBW() - bidReceiver);

		// set the receiver's down bw to the subtraction of its current down bw and bidSender
		receiver->getCurrentBandwidth()->resetBandwidth(receiver->getCurrentBandwidth()->getDownBW() - bidReceiver,
														receiver->getCurrentBandwidth()->getUpBW());

		return true;
	}
	else {
		return false;
	}
}

std::set<std::shared_ptr<GnpNetBandwidthAllocation>> GnpNetBandwidthManager::getChangedAllocations() {
	std::cout<<"changedAllocations size:"<<changedAllocations.size()<<std::endl;
	return changedAllocations;
}
