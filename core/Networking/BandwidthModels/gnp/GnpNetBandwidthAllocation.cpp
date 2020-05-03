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

#include <cmath>

#include "./GnpNetBandwidthAllocation.h"

GnpNetBandwidthAllocation::GnpNetBandwidthAllocation(NodeId _sender, NodeId _receiver) {
	sender = _sender;
	receiver = _receiver;
	bidSender[0] = 0;
	bidSender[1] = 0;
	bidReciever[0] = 0;
	bidReciever[1] = 0;
}

double GnpNetBandwidthAllocation::getAllocatedBandwidth() {
	return allocatedBandwidth;
}

void GnpNetBandwidthAllocation::setAllocatedBandwidth(double _allocatedBandwidth) {
	allocatedBandwidth = _allocatedBandwidth;
}

double GnpNetBandwidthAllocation::getBandwidthNeeds() {
	return bandwidthNeeds;
}

void GnpNetBandwidthAllocation::setBandwidthNeeds(double _bandwidthNeeds) {
	bandwidthNeeds = _bandwidthNeeds;
}

NodeId GnpNetBandwidthAllocation::getReceiver() {
	return receiver;
}

NodeId GnpNetBandwidthAllocation::getSender() {
	return sender;
}

void GnpNetBandwidthAllocation::initConnection() {
	bidSender[0] = 0;
	bidSender[1] = 0;
	bidReciever[0] = 0;
	bidReciever[1] = 0;
	minBidSender = false;
	minBidReceiver = false;

//	sender.setCurrentBandwidth(new Bandwidth(
//			sender.getCurrentBandwidth().getDownBW(), sender.getMaxBandwidth().getUpBW()));
//
//
//	receiver.setCurrentBandwidth(new Bandwidth(
//			sender.getMaxBandwidth().getDownBW(), receiver.getCurrentBandwidth().getUpBW()));
}

void GnpNetBandwidthAllocation::setBid(double bid, bool isMinimal, bool sender, long step) {
	if (sender) {
		int posC = (int) (step % 2);
		bidSender[posC] = bid;
		minBidSender = isMinimal;
	} else {
		int posC = (int) (step % 2);
		bidReciever[posC] = bid;
		minBidReceiver = isMinimal;
	}
}

double GnpNetBandwidthAllocation::getCurrentBid(bool forSender, long step) {
	if (forSender) {
		return bidSender[(int) (step % 2)];
	} else {
		return bidReciever[(int) (step % 2)];
	}
}

double GnpNetBandwidthAllocation::getPreviousBid(bool forSender, long step) {
	if (forSender) {
		return bidSender[(int) ((step + 1) % 2)];
	} else {
		return bidReciever[(int) ((step + 1) % 2)];
	}
}

bool GnpNetBandwidthAllocation::isBidRepeated(bool forSender) {
	if (forSender) {
		return std::fabs(bidSender[0] - bidSender[1]) <= 0.0001;
	} else {
		return std::fabs(bidReciever[0] - bidReciever[1]) <= 0.0001;
	}
}

bool GnpNetBandwidthAllocation::isMinBid(bool forSender) {
	if (forSender) {
		return minBidSender;
	} else {
		return minBidReceiver;
	}
}
