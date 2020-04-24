#ifndef CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_

#include "../../Network/Node/NodeId.h"

class LatencyModel {
	void getLatency(NodeId _sender, NodeId _receiver) = 0;
};

#endif /* CORE_NETWORKING_LATENCYMODELS_LATENCYMODEL_H_ */
