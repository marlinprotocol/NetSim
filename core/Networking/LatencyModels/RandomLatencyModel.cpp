#include <cmath>
#include <functional>

#include "RandomLatencyModel.h"
#include "../../../helpers/Random.h"

int getDistance(NodeId _sender, NodeId _receiver) {
	return 1000;
}

double RandomLatencyModel::calcStaticDelay(NodeId _sender, NodeId _receiver) {
    std::hash<int> hash_int;
	int df = hash_int(_receiver);
	return (df + (getDistance(_sender, _receiver) / speedOfLight) * 100);
}

long long RandomLatencyModel::getLatency(NodeId _sender, NodeId _receiver) {
	double staticDelay = calcStaticDelay(_sender, _receiver);
	int f = Random::getRandomInstance().getInt(10) + 1;
	return std::llround(f * staticDelay * 0.1);
}
