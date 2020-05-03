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

#include <iostream>
#include <set>

#include "AbstractGnpNetBandwidthManager.h"
#include "GnpNetBandwidthAllocation.h"
#include "../../Bandwidth.h"
#include "../../../Network/Network.h"

AbstractGnpNetBandwidthManager::AbstractGnpNetBandwidthManager(Network& _network) : network(_network) {}

std::shared_ptr<GnpNetBandwidthAllocation> AbstractGnpNetBandwidthManager::addConnection(NodeId _sender, NodeId _receiver, double bandwidth) {
	if(connectionsSenderToReceiver.find(_sender) == connectionsSenderToReceiver.end() ||
			connectionsSenderToReceiver[_sender].find(_receiver) == connectionsSenderToReceiver[_sender].end()) {
		connectionsSenderToReceiver[_sender][_receiver] = std::make_shared<GnpNetBandwidthAllocation>(_sender, _receiver);
	}

	std::shared_ptr<GnpNetBandwidthAllocation> c = connectionsSenderToReceiver[_sender][_receiver];

	connectionsReceiverToSender[_receiver][_sender] = c;

	c->setAllocatedBandwidth(0);

	auto senderCurrentBandwidth = network.getNode(_sender)->getCurrentBandwidth();
	auto senderMaxBandwidth = network.getNode(_sender)->getMaxBandwidth();
	auto receiverCurrentBandwidth = network.getNode(_receiver)->getCurrentBandwidth();
	auto receiverMaxBandwidth = network.getNode(_receiver)->getMaxBandwidth();

	// set senders up bandwidth to the sender's max up bandwidth
	senderCurrentBandwidth->resetBandwidth(senderCurrentBandwidth->getDownBW(), senderMaxBandwidth->getUpBW());
	/*
	 * set the receiver's down bandwidth to the sender's max down bandwidth CHECK did we really want to do this?
	 * Maybe we have to adjust it to set the receiver's down bandwidth to the receiver's max down bandwidth?!
	 */
	receiverCurrentBandwidth->resetBandwidth(receiverMaxBandwidth->getDownBW(), receiverCurrentBandwidth->getUpBW());
	c->setBandwidthNeeds(c->getBandwidthNeeds() + bandwidth);

	return c;
}

std::shared_ptr<GnpNetBandwidthAllocation> AbstractGnpNetBandwidthManager::removeConnection(NodeId _sender, NodeId _receiver, double _bandwidth) {
	std::shared_ptr<GnpNetBandwidthAllocation> ba;

	if (connectionsSenderToReceiver.find(_sender) != connectionsSenderToReceiver.end()) {
		if (connectionsSenderToReceiver[_sender].find(_receiver) != connectionsSenderToReceiver[_sender].end()) {
			ba = connectionsSenderToReceiver[_sender][_receiver];
			if (_bandwidth < 0) {
				ba->setBandwidthNeeds(0);
			}
			else {
				ba->setBandwidthNeeds(ba->getBandwidthNeeds() - _bandwidth);
			}
			if (ba->getBandwidthNeeds() == 0.0) {
				connectionsSenderToReceiver[_sender].erase(_receiver);
				if (connectionsSenderToReceiver[_sender].empty()) {
					connectionsSenderToReceiver.erase(_sender);
				}
				connectionsReceiverToSender[_receiver].erase(_sender);
				if (connectionsReceiverToSender[_receiver].empty()) {
					connectionsReceiverToSender.erase(_receiver);
				}
			}
			ba->setAllocatedBandwidth(0);
		}
	}

	auto senderCurrentBandwidth = network.getNode(_sender)->getCurrentBandwidth();
	auto senderMaxBandwidth = network.getNode(_sender)->getMaxBandwidth();
	auto receiverCurrentBandwidth = network.getNode(_receiver)->getCurrentBandwidth();
	auto receiverMaxBandwidth = network.getNode(_receiver)->getMaxBandwidth();

	// set senders up bandwidth to the sender's max up bandwidth
	senderCurrentBandwidth->resetBandwidth(senderCurrentBandwidth->getDownBW(), senderMaxBandwidth->getUpBW());
	/*
	 * set the receiver's down bandwidth to the sender's max down bandwidth CHECK did we really want to do this?
	 * Maybe we have to adjust it to set the receiver's down bandwidth to the receiver's max down bandwidth?!
	 */
	receiverCurrentBandwidth->resetBandwidth(receiverMaxBandwidth->getDownBW(), receiverCurrentBandwidth->getUpBW());
	return ba;
}

std::set<std::shared_ptr<GnpNetBandwidthAllocation>> AbstractGnpNetBandwidthManager::removeConnections(NodeId _nodeId) {
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> connections;

	for (auto it: connectionsSenderToReceiver[_nodeId]) {
		connections.insert(removeConnection(_nodeId, it.first, -1));
	}

	for (auto it: connectionsReceiverToSender[_nodeId]) {
		connections.insert(removeConnection(it.first, _nodeId, -1));
	}

	return connections;
}

std::shared_ptr<GnpNetBandwidthAllocation> AbstractGnpNetBandwidthManager::getBandwidthAllocation(NodeId _sender, NodeId _receiver) {
	if (connectionsSenderToReceiver.find(_sender) != connectionsSenderToReceiver.end()) {
		if (connectionsSenderToReceiver[_sender].find(_receiver) != connectionsSenderToReceiver[_sender].end()) {
			return connectionsSenderToReceiver[_sender][_receiver];
		}
	}
	return nullptr;
}
