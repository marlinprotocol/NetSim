#include "./BitcoinModel.h"
#include "../../core/Blockchain/Block/PoWBlock.h"
#include "../../core/Network/Node/Miner.h"

BitcoinModel::BitcoinModel(Network &_network): exp(1.0/600), unif(0, 1), network(_network) {
	// initiaze random number generator, seed fixed to 22 to make it deterministic across runs
	// else make it time-dependent for randomness	
	uint64_t seed = 22;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
    rng.seed(ss);
}

void BitcoinModel::OnOutOfRangeNewBlockArrival() {

}

uint64_t BitcoinModel::getNextBlockTime() {
	LOG(INFO) << "[BitcoinModel::getNextBlockTime start; network.getTotalLambda(): "
			  << network.getTotalLambda() << "]";
	std::exponential_distribution<double> exp2(network.getTotalLambda());
	return (uint64_t) exp2(rng);
}

std::shared_ptr<Node> BitcoinModel::getNextBlockProducer() {
	LOG(INFO) << "[BitcoinModel::getNextBlockProducer start]";

	std::shared_ptr<Node> blockProducer = network.pickLambdaWeightedNode();

	LOG(INFO) << "[BitcoinModel::getNextBlockProducer end]";

	return blockProducer;
}

int BitcoinModel::getNextBlockProducerId() {
	LOG(INFO) << "[BitcoinModel::getNextBlockProducer start]";

	std::shared_ptr<Node> blockProducer = network.pickLambdaWeightedNode();

	LOG(INFO) << "[BitcoinModel::getNextBlockProducer end]";

	return blockProducer->getNodeId();
}

std::shared_ptr<Block> BitcoinModel::createGenesisBlock() {
	int genesisBlockId;
	
	std::shared_ptr<Block> genesisBlock = getGenesisPoWBlock();

	LOG(INFO) << "[GenesisBlock Bitcoin with id " << genesisBlock->getBlockId() << " created]";

	return genesisBlock;
}
