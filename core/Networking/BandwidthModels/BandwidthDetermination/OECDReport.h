#ifndef CORE_NETWORKING_BANDWIDTHMODELS_BANDWIDTHDETERMINATION_OECDREPORT_H_
#define CORE_NETWORKING_BANDWIDTHMODELS_BANDWIDTHDETERMINATION_OECDREPORT_H_

#include <random>
#include <vector>

class Bandwidth;

class OECDReport {
private:
	std::vector<Bandwidth> bandwidthValues;
	std::vector<double> distribution;
	double totalDistribution;
	std::mt19937_64 rng;
	std::uniform_real_distribution<double> unif;

public:
	OECDReport();
	bool addNewBandwidthValue(double uploadBandwidth, double downloadBandwidth, double distributionFraction);
	std::shared_ptr<Bandwidth> getRandomBandwidth();
};

#endif /* CORE_NETWORKING_BANDWIDTHMODELS_BANDWIDTHDETERMINATION_OECDREPORT_H_ */
