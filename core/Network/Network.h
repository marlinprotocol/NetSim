#ifndef NETWORK_H_
#define NETWORK_H_

#include <memory>
#include <random>
#include <vector>

#include "./Node/Node.h"
#include "../../helpers/Logger/easylogging.h"

class Network {
private:
	std::mt19937_64 rng;
	std::uniform_real_distribution<double> unif;
	std::vector<std::shared_ptr<Node>> nodes;
	std::unordered_map<NodeId, std::shared_ptr<Node>> nodeIdToNodePtr;
	double totalLambda;
	std::vector<double> cumulativeLambdaVector;

public:
	Network();
	bool addNode(std::shared_ptr<Node> node);
	std::shared_ptr<Node> getNode(NodeId nodeId);
	std::vector<std::shared_ptr<Node>> getNodes() const;
	double getTotalLambda() const;
	double recaculateTotalLambda();
	std::vector<double> recaculateCumulativeLambdaVector();
	std::shared_ptr<Node> pickLambdaWeightedNode();
};

#endif /*NETWORK_H_*/
