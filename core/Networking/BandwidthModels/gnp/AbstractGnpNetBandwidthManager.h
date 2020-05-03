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

#ifndef CORE_NETWORKING_BANDWIDTHMODELS_GNP_ABSTRACTGNPNETBANDWIDTHMANAGER_H_
#define CORE_NETWORKING_BANDWIDTHMODELS_GNP_ABSTRACTGNPNETBANDWIDTHMANAGER_H_

#include <unordered_map>

#include "../../../Network/Node/NodeId.h"

class Network;
class GnpNetBandwidthAllocation;

class AbstractGnpNetBandwidthManager {
protected:
	Network& network;
	std::unordered_map<NodeId, std::unordered_map<NodeId, std::shared_ptr<GnpNetBandwidthAllocation>>> connectionsReceiverToSender;
	std::unordered_map<NodeId, std::unordered_map<NodeId, std::shared_ptr<GnpNetBandwidthAllocation>>> connectionsSenderToReceiver;

public:
	AbstractGnpNetBandwidthManager(Network& _network);
	virtual ~AbstractGnpNetBandwidthManager() {};
	std::shared_ptr<GnpNetBandwidthAllocation> addConnection(NodeId _sender, NodeId _receiver, double _bandwidth);
	std::shared_ptr<GnpNetBandwidthAllocation> removeConnection(NodeId _sender, NodeId _receiver, double _bandwidth);
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> removeConnections(NodeId _nodeId);
	std::shared_ptr<GnpNetBandwidthAllocation> getBandwidthAllocation(NodeId _sender, NodeId _receiver);
	virtual void allocateBandwidth() = 0;
	virtual std::set<std::shared_ptr<GnpNetBandwidthAllocation>> getChangedAllocations() = 0;
};

#endif /* CORE_NETWORKING_BANDWIDTHMODELS_GNP_ABSTRACTGNPNETBANDWIDTHMANAGER_H_ */
