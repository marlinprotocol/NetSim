#ifndef BTCMODEL_H_
#define BTCMODEL_H_

#include <random>

#include "../../../core/Network/Network.h"
#include "../../../core/Network/Node/Miner.h"
#include "../../../helpers/Logger/easylogging.h"
#include "GlobalOrchestration.h"

class BitcoinModel : public GlobalOrchestration {
	std::mt19937_64 rng;
	std::exponential_distribution<double> exp;
	std::uniform_real_distribution<double> unif;
	Network &network;
	uint64_t getRandomNumFromExponentialDistribution();

public:
	BitcoinModel(Network &network);
	uint64_t getNextBlockTime();
	std::shared_ptr<Node> getNextBlockProducer();
	int getNextBlockProducerId();
	std::shared_ptr<Block> createGenesisBlock();
	void scheduleNextBlock(EventManager* eventManager);
};

#endif /*BTCMODEL_H_*/
