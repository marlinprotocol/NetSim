#include "StaticLatencyModel.h"

StaticLatencyModel::StaticLatencyModel() : delayPerUnitDistance(5) {};

StaticLatencyModel::StaticLatencyModel(int _delayPerUnitDistance) : delayPerUnitDistance(_delayPerUnitDistance) {};

void StaticLatencyModel::setLatencyParameter(long _delayPerUnitDistance) {
	delayPerUnitDistance = _delayPerUnitDistance;
}

int getDistance(NodeId _sender, NodeId _receiver) {
	return 1;
}

long long StaticLatencyModel::getLatency(NodeId _sender, NodeId _receiver) {
	long long latency = delayPerUnitDistance * getDistance(_sender, _receiver);
	return latency;
}
