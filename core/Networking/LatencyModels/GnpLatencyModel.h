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

// ported to C++ for Marlin Protocol

#ifndef CORE_NETWORKING_LATENCYMODELS_GNPLATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_GNPLATENCYMODEL_H_

#include <memory>

#include "LatencyModel.h"
#include "PingER.h"
#include "../../Network/Node/NodeId.h"

class IPv4Message;
class Network;

class GnpLatencyModel : public LatencyModel {
private:
	static int MSS;
	Network& network;
	PingER pingER;

public:
	GnpLatencyModel(Network& _network);
//	void setPingER(PingER& _pingER);
	PingER& getPingER();
	double getMinRTT(NodeId sender, NodeId receiver);
	double getPacketLossProbability(NodeId senderId, NodeId receiverId);
	double getNextJitter(NodeId senderId, NodeId receiverId);
	double getAvgJitter(NodeId senderId, NodeId receiverId);
	double getUDPErrorProbability(NodeId senderId, NodeId receiverId, std::shared_ptr<IPv4Message> _msg);
	uint64_t getTransmissionDelay(long long _bytes, double _bandwidth);
	uint64_t getPropagationDelay(NodeId _sender, NodeId _receiver);
	uint64_t getTCPThroughput(NodeId sender, NodeId receiver, bool _useJitter);
	long long getLatency(NodeId _sender, NodeId _receiver);
};

#endif /* CORE_NETWORKING_LATENCYMODELS_GNPLATENCYMODEL_H_ */
