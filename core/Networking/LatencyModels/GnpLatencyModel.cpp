#include <cmath>

#include "GnpLatencyModel.h"
#include "../NetworkLayer/IPv4Message.h"
#include "../TransportLayer/L4Message.h"

double GnpLatencyModel::getUDPErrorProbability(std::shared_ptr<IPv4Message> msg) {
//	if(msg->getPayload()->getSize() > 65507) {
//		// warn("Message-Size is too big for a UDP-Datagramm (max 65507 byte)");
//	}
//
//	double lp = getPacketLossProbability(sender, receiver);

	return 0;
}

uint64_t GnpLatencyModel::getTransmissionDelay(long long bytes, double bandwidth) {
	return round(bytes/bandwidth);
}

uint64_t GnpLatencyModel::getPropagationDelay(NodeId sender, NodeId receiver) {
	return 0;
}

uint64_t GnpLatencyModel::getTCPThroughput(NodeId sender, NodeId receiver) {
	return 0;
}

long long GnpLatencyModel::getLatency(NodeId _sender, NodeId _receiver) {
	return getPropagationDelay(_sender, _receiver);
}
