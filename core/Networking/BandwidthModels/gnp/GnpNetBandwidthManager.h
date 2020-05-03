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

#ifndef CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHMANAGER_H_
#define CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHMANAGER_H_

#include <unordered_map>
#include <set>

#include "AbstractGnpNetBandwidthManager.h"

class Network;;
class GnpNetBandwidthAllocation;

class GnpNetBandwidthManager : public AbstractGnpNetBandwidthManager {
private:
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> tempConnections;
	std::unordered_map<NodeId, std::set<std::shared_ptr<GnpNetBandwidthAllocation>>> tempSenderConnections;
	std::unordered_map<NodeId, std::set<std::shared_ptr<GnpNetBandwidthAllocation>>> tempReceiverConnections;
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> changedAllocations;
	long step = 0;

public:
	GnpNetBandwidthManager(Network& _network);
	void allocateBandwidth();
	int generateMeanBids(double bandwidth, std::set<std::shared_ptr<GnpNetBandwidthAllocation>> unassigned, bool isSender);
	bool generateMinimumBids(NodeId p, bool sender);
	bool assignAllocation(std::shared_ptr<GnpNetBandwidthAllocation> c);
	std::set<std::shared_ptr<GnpNetBandwidthAllocation>> getChangedAllocations();
};

#endif /* CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHMANAGER_H_ */
