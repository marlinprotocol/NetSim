#ifndef CORE_NETWORKING_LATENCYMODELS_LINKMETRICS_H_
#define CORE_NETWORKING_LATENCYMODELS_LINKMETRICS_H_

class LinkMetrics {
private:
	double minRTT;
	double avgRTT;
	double packetLoss;

public:
	LinkMetrics();
	LinkMetrics(double _minRTT, double _avgRTT, double _packetLoss);
	LinkMetrics(const LinkMetrics& _linkMetrics);
	double getMinRTT();
	double getAvgRTT();
	double getPacketLoss();
};

#endif /* CORE_NETWORKING_LATENCYMODELS_LINKMETRICS_H_ */
