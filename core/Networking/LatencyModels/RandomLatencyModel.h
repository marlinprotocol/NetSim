#ifndef CORE_NETWORKING_LATENCYMODELS_RANDOMLATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_RANDOMLATENCYMODEL_H_

#include "LatencyModel.h"

class RandomLatencyModel : public LatencyModel {
private:
	int speedOfLight = 300000; // km per sec

public:
	RandomLatencyModel();
	long long getLatency(NodeId _sender, NodeId _receiver);
	double calcStaticDelay(NodeId _sender, NodeId _receiver);
};

#endif /* CORE_NETWORKING_LATENCYMODELS_RANDOMLATENCYMODEL_H_ */
