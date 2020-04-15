#include <algorithm>
#include <random>

#include "./Network.h"
#include "./Node/Miner.h"

Network::Network(): unif(0, 1), totalLambda(0) {
	// initiaze random number generator, seed fixed to 22 to make it deterministic across runs
	// else make it time-dependent for randomness
	uint64_t seed = 93;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
    rng.seed(ss);
}

bool Network::addNode(std::shared_ptr<Node> node) {
	nodes.push_back(node);
	return true;
}

std::vector<std::shared_ptr<Node>> Network::getNodes() const {
	return nodes;
}

double Network::getTotalLambda() {
	return totalLambda;
}

double Network::recaculateTotalLambda() {
	double sum = 0.0;

	if (nodes.size() != 0 && std::static_pointer_cast<Miner>(nodes[0]) != nullptr) { // TODO: make getLambda a function of Node if required for other subclasses as well
		for(std::shared_ptr<Node> node: nodes) {
			auto n = std::dynamic_pointer_cast<Miner>(node);
			sum += n->getLambda();
		}
	}

	totalLambda = sum;

	return totalLambda;
}

std::vector<double> Network::recaculateCumulativeLambdaVector() {
	std::vector<double> v;

	if (nodes.size() != 0 && std::static_pointer_cast<Miner>(nodes[0]) != nullptr) { // TODO: make getLambda a function of Node if required for other subclasses as well
		for(int i=0; i<nodes.size(); i++) {
			std::shared_ptr<Miner> miner = std::static_pointer_cast<Miner>(nodes[i]);

			if(i==0)
				v.push_back(miner->getLambda());
			else
				v.push_back(v[i-1] + miner->getLambda());

			// LOG(DEBUG) << "[" << std::setw(35) << std::left << "BitcoinModel::getNextBlockProducer]"
			// 	       << "[NodeId: " << i << ", CumulativeHash: "  << hashpowerFraction[i] << "]";
		}
	}

	cumulativeLambdaVector = v;

	return v;
}

std::shared_ptr<Node> Network::pickLambdaWeightedNode() {
	std::shared_ptr<Node> node;

	auto it = std::upper_bound(cumulativeLambdaVector.begin(),
							   cumulativeLambdaVector.end(), totalLambda);

	int index = it - cumulativeLambdaVector.begin();

	return nodes[index];
}
