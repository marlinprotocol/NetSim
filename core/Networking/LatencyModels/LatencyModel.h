#ifndef CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_

#include <memory>

#include "../../Network/Node/NodeId.h"

class IPv4Message;

class LatencyModel {
public:
	virtual ~LatencyModel() = 0;
	virtual long long getLatency(NodeId _sender, NodeId _receiver) = 0;
	virtual double getUDPErrorProbability(NodeId senderId, NodeId receiverId, std::shared_ptr<IPv4Message> msg) = 0;
};

#endif /* CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_ */
