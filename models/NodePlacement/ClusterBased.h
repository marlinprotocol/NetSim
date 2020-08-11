#ifndef RANDOMNODELOCATIONS_H_
#define RANDOMNODELOCATIONS_H_

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "../LocalProtocols/BitcoinMiner.h"
#include "../../helpers/Center.h"
#include "../../helpers/Logger/easylogging.h"
#include "../../config/Config.h"
#include "../../core/Network/Network.h"
#include "../../core/Network/Node/Node.h"
#include "../../core/Network/Node/NodeType.h"
#include "../../core/Networking/RoutingTable.h"
#include "../BlockchainManagement/GlobalOrchestration/GlobalOrchestration.h"
#include "../../core/Networking/LatencyModels/WonderNetwork.h"

bool generateNodes(Network& network, std::shared_ptr<BlockCache> blockCache, NodeType nodeType,
				   std::shared_ptr<GlobalOrchestration> _blockchainManagementModel,
				   std::shared_ptr<Subnet> _subnet) {
	std::vector<double> cumulativeProbabilities;

	// compute cumulative probability vector of node distribution in regions to randomly assign a node's region
	for(int i=0; i<NUM_REGIONS; i++) {
		if(i==0)
			cumulativeProbabilities.push_back(REGION_DISTRIBUTION_OF_NODES[0]);
		else
			cumulativeProbabilities.push_back(
				cumulativeProbabilities[i-1] + REGION_DISTRIBUTION_OF_NODES[i]);
	}

	if(cumulativeProbabilities[NUM_REGIONS-1] != 1) {
		LOG(FATAL) << "Probabilities in REGION_DISTRIBUTION_OF_NODES do not add up to 1. Sum obtained: "
				   << cumulativeProbabilities[NUM_REGIONS-1];
		return false;
	}

	// initiaze random number generator, seed fixed to 2121 to make it deterministic across runs
	// else make it time-dependent for randomness
	std::mt19937_64 rng;
	uint64_t seed = 2121;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
    rng.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);

	LOG(INFO) << "Creating cluster nodes";

    // create Nodes and assign their regions based on the index of generated random number in the cumulative probability vector
	for(int i = 0; i < NUM_CLUSTERS; i++) {
		for(int j = 0; j < CLUSTER_SIZE; j++) {
			double randomNumber = unif(rng);
			for(int k = 0; k < NUM_REGIONS; k++) {
				if(cumulativeProbabilities[k] >= randomNumber) {
					int regionIdx = k; // TODO
					int cityIdx;

					int nodeIdx = i * CLUSTER_SIZE + j;
					std::shared_ptr<Node> node(new Node(nodeIdx, true, regionIdx, cityIdx, blockCache, _subnet, "FlexibleRoutingTable"));
					for(int l = 0; l < CLUSTER_SIZE; l++) {
						if(j != l) {
							node->getRoutingTable()->addOutConnection(i * CLUSTER_SIZE + l);
						}
					}
					network.addNode(node);
					break;
				}
			}
		}
	}

	LOG(INFO) << "Creating miner nodes";

	const int MINER_OFFSET = NUM_CLUSTERS * CLUSTER_SIZE;
	for(int i = 0; i < NUM_MINERS; i++) {
		double randomNumber = unif(rng);
		for(int j = 0; j < NUM_REGIONS; j++) {
			if(cumulativeProbabilities[j] >= randomNumber) {
				int regionIdx = j; // TODO
				int cityIdx;
				int nodeIdx = MINER_OFFSET + i;
				std::shared_ptr<Node> node(new Node(nodeIdx, true, regionIdx, cityIdx, blockCache, _subnet, "FlexibleRoutingTable"));
				std::shared_ptr<BitcoinMiner> bitcoinMinerProtocol(new BitcoinMiner(node, i%2==0?1:2, (NUM_MINERS/2*2 + (NUM_MINERS/2)) * BLOCK_TIME));
				node->addProtocol(std::static_pointer_cast<Protocol>(bitcoinMinerProtocol));

				for(int k = 0; k < NUM_CLUSTERS; k++) {
					double otherRandomNumber = unif(rng);
					int randomNodeInClusterIdx = k * CLUSTER_SIZE + int(otherRandomNumber * CLUSTER_SIZE);
					node->getRoutingTable()->addOutConnection(randomNodeInClusterIdx);
				}
				network.addNode(node);
				break;
			}
		}
	}

	LOG(INFO) << "Created miner nodes";

	network.recaculateTotalLambda();
	LOG(INFO) << "first done";
	network.recaculateCumulativeLambdaVector();

	LOG(INFO) << "Sab ho gaya";

	return true;
}

bool printGeneratedNetwork(const Network& network) {
	LOG(INFO) << "[PRINT_GENERATED_NETWORK_START]";

	int numNodesPerRegion[NUM_REGIONS] = {0};

	const std::vector<std::shared_ptr<Node>> nodes = network.getNodes();

	for(auto node: nodes) {
		numNodesPerRegion[node->getRegion()]++;
	}

	el::Logger* networkTopologyLogger = el::Loggers::getLogger("networkTopology");

	CLOG(INFO, "networkTopology") << std::setw(13) << centered("REGION_ID")
								  << std::setw(20) << centered("REGION")
								  << std::setw(20) << centered("EXPECTED")
								  << std::setw(20) << centered("GENERATED");

	for(int i=0; i<NUM_REGIONS; i++) {
		CLOG(INFO, "networkTopology") << std::setw(13) << centered(std::to_string(i))
									  << std::setw(20) << centered(REGIONS[i])
								  	  << std::setw(20) << centered(std::to_string(REGION_DISTRIBUTION_OF_NODES[i] * NUM_NODES))
								 	  << std::setw(20) << centered(std::to_string(numNodesPerRegion[i]));
	}


	// printing adjacency list.
	for(auto node: nodes) {
		std::set <int> outConnections = node->getRoutingTable()->getOutConnections();
		LOG(INFO) << node->getNodeId();
		for(auto idx: outConnections) {
			LOG(INFO) << idx << ' ';
		}
		LOG(INFO) << "\n";
	}

	LOG(INFO) << "[PRINT_GENERATED_NETWORK_END]";

	return true;
}

//bool initializeRoutingTable(const Network& network) {
//	LOG(INFO) << "[INITIALIZE_ROUTING_TABLE_START]";
//
//	const std::vector<std::shared_ptr<Node>> nodes = network.getNodes();
//
//	for(auto node: nodes) {
//
//	}
//
//	LOG(INFO) << "[INITIALIZE_ROUTING_TABLE_END]";
//
//	return true;
//}

Network getRandomNetwork(std::shared_ptr<BlockCache> _blockCache,
						 std::shared_ptr<GlobalOrchestration> _blockchainManagementModel,
						 std::shared_ptr<Subnet> _subnet) {
	LOG(INFO) << "[Something something]";
	Network network;
	LOG(INFO) << "[Something something]";
	WonderNetwork wonderNetwork = WonderNetwork();

	generateNodes(network, _blockCache, NodeType::Miner, _blockchainManagementModel, _subnet);
	printGeneratedNetwork(network);

//	initializeRoutingTable(network);

	return network;
}

#endif /*RANDOMNODELOCATIONS_H_*/
