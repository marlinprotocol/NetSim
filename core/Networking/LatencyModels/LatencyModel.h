#ifndef CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_

#include "../../Network/Node/NodeId.h"

class LatencyModel {
public:
	virtual ~LatencyModel();
	virtual long long getLatency(NodeId _sender, NodeId _receiver) = 0;
	virtual double getUDPErrorProbability(std::shared_ptr<IPv4Message> msg) = 0;
};

#endif /* CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_ */
