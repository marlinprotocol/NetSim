#include <algorithm>
#include <random>
#include <vector>

#include "./Network.h"
#include "../../models/LocalProtocols/BitcoinMiner.h"

Network::Network(): unif(0, 1), totalLambda(0) {
	// initiaze random number generator, seed fixed to 22 to make it deterministic across runs
	// else make it time-dependent for randomness
	uint64_t seed = 93;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
    rng.seed(ss);
}

bool Network::addNode(std::shared_ptr<Node> node) {
	nodes.push_back(node);
	nodeIdToNodePtr.insert(make_pair(node->getNodeId(), node));
	return true;
}

std::shared_ptr<Node> Network::getNode(NodeId nodeId) {
	return nodeIdToNodePtr[nodeId];
}

std::vector<std::shared_ptr<Node>> Network::getNodes() const {
	return nodes;
}

double Network::getTotalLambda() const {
	return totalLambda;
}

double Network::recaculateTotalLambda() {
	double sum = 0.0;
	if (nodes.size() != 0 && nodes[0] != nullptr) { // TODO: make getLambda a function of Node if required for other subclasses as well
		for(std::shared_ptr<Node> node: nodes) {
			if(node->getProtocols().empty()) {
				continue;
			}
			auto n = std::static_pointer_cast<Protocol>(node->getProtocols()[0]);
			sum += n->getLambda();
		}
	}

	totalLambda = sum;

	return totalLambda;
}

std::vector<double> Network::recaculateCumulativeLambdaVector() {
	std::vector<double> v;

	if (nodes.size() != 0 && nodes[0] != nullptr) { // TODO: make getLambda a function of Node if required for other subclasses as well
		for(int i=0; i<nodes.size(); i++) {
			if(nodes[i]->getProtocols().empty()) {
				continue;
			}
			auto miner = std::static_pointer_cast<Protocol>(nodes[i]->getProtocols()[0]);
			// LOG(INFO) << "debug here";
			if(v.empty())
				v.push_back(miner->getLambda());
			else
				v.push_back(v.back() + miner->getLambda());

			// LOG(DEBUG) << "[" << std::setw(35) << std::left << "BitcoinModel::getNextBlockProducer]"
			// 	       << "[NodeId: " << i << ", CumulativeHash: "  << hashpowerFraction[i] << "]";
		}
	}

	cumulativeLambdaVector = v;

	return v;
}

double Network::getRandomDouble() {
	return unif(rng);
}

std::shared_ptr<Node> Network::pickLambdaWeightedNode() {
	std::shared_ptr<Node> node;

	double randomNumber = getRandomDouble() * totalLambda;
	std::cout << randomNumber << ' ' << totalLambda << ' ' << std::endl;
	for(double x: cumulativeLambdaVector) {
		std::cout << x << ' '<< std::endl;
	}

	auto it = std::upper_bound(cumulativeLambdaVector.begin(),
							   cumulativeLambdaVector.end(), randomNumber);

	int index = it - cumulativeLambdaVector.begin();
	std::cout << nodes.size() << ' ' << index << std::endl;
	return nodes[index];
}
