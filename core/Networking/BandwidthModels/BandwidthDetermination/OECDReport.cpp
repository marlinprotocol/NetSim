

#include "OECDReport.h"

OECDReport::OECDReport() : unif(0, 1) {
	totalDistribution = 0;
	// initiaze random number generator, seed fixed to 2121 to make it deterministic across runs
	// else make it time-dependent for randomness
	uint64_t seed = 2222;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
    rng.seed(ss);
}

bool OECDReport::addNewBandwidthValue(double uploadBandwidth, double downloadBandwidth, double distributionFraction) {
	bandwidthValues.push_back(Bandwidth(uploadBandwidth, downloadBandwidth));
	distribution.push_back(distributionFraction);
	totalDistribution += distributionFraction;
	return true;
}

std::shared_ptr<Bandwidth> OECDReport::getRandomBandwidth() {
    std::shared_ptr<Bandwidth> bandwidth;

    double randomNumber = unif(rng) * totalDistribution;
    double sum = 0;

    for(int i=0; i<distribution.size(); i++) {
    	sum += distribution[i];
    	if(randomNumber < sum) {
    		bandwidth = std::make_shared<Bandwidth>(bandwidthValues[i]);
    	}
    }

    return bandwidth;
}
