#include "LinkMetrics.h"

LinkMetrics::LinkMetrics()
			: minRTT(0), avgRTT(0), packetLoss(0) {}

LinkMetrics::LinkMetrics(double _minRTT, double _avgRTT, double _packetLoss)
			: minRTT(_minRTT), avgRTT(_avgRTT), packetLoss(_packetLoss) {}

LinkMetrics::LinkMetrics(const LinkMetrics& _linkMetrics)
			: minRTT(_linkMetrics.minRTT), avgRTT(_linkMetrics.avgRTT), packetLoss(_linkMetrics.packetLoss) {}

double LinkMetrics::getMinRTT() {
	return minRTT;
}

double LinkMetrics::getAvgRTT() {
	return avgRTT;
}

double LinkMetrics::getPacketLoss() {
	return packetLoss;
}
