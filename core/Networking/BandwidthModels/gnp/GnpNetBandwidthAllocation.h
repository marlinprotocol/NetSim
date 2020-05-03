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

#ifndef CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHALLOCATION_H_
#define CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHALLOCATION_H_

#include "../../../Network/Node/NodeId.h"

class GnpNetBandwidthAllocation {
private:
	double allocatedBandwidth = 0.0;
	double bandwidthNeeds = 0.0;
	NodeId receiver;
	NodeId sender;
	double bidSender[2];
	double bidReciever[2];
	bool minBidSender = false;
	bool minBidReceiver = false;

public:
	GnpNetBandwidthAllocation(NodeId _sender, NodeId _receiver);
	double getAllocatedBandwidth();
	void setAllocatedBandwidth(double _allocatedBandwidth);
	double getBandwidthNeeds();
	void setBandwidthNeeds(double _bandwidthNeeds);
	NodeId getReceiver();
	NodeId getSender();
	void initConnection();
	void setBid(double bid, bool isMinimal, bool sender, long step);
	double getCurrentBid(bool forSender, long step);
	double getPreviousBid(bool forSender, long step);
	bool isBidRepeated(bool forSender);
	bool isMinBid(bool forSender);
};

#endif /* CORE_NETWORKING_BANDWIDTHMODELS_GNP_GNPNETBANDWIDTHALLOCATION_H_ */
