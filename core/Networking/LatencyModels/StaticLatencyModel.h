#ifndef CORE_NETWORKING_LATENCYMODELS_STATICLATENCYMODEL_H_
#define CORE_NETWORKING_LATENCYMODELS_STATICLATENCYMODEL_H_

#include "LatencyModel.h"

class StaticLatencyModel : public LatencyModel {
private:
	int delayPerUnitDistance;

public:
	StaticLatencyModel();
	StaticLatencyModel(int _delayPerUnitDistance);
	void setLatencyParameter(long _delayPerUnitDistance);
	long long getLatency(NodeId _sender, NodeId _receiver);
};

#endif /* CORE_NETWORKING_LATENCYMODELS_STATICLATENCYMODEL_H_ */
