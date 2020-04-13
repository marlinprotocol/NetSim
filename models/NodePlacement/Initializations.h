#ifndef INITIALIZATIONS_H_
#define INITIALIZATIONS_H_

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "../../helpers/Center.h"
#include "../../helpers/Logger/easylogging.h"
#include "../../config/Config.h"
#include "../../core/Blockchain/Cache/BlockCache.h"
#include "../../core/Network/Network.h"
#include "../../core/Network/Node/Miner.h"
#include "../../core/Network/Node/Node.h"
#include "../../core/Network/Node/NodeType.h"
#include "../../core/Networking/RoutingTable.h"
#include "../../models/BlockchainManagementModels/BitcoinModel.h"

void sendGenesisBlockToAllNodes(const Network& network, int _genesisBlockId, EventManager& eventManager) {
	for(auto nodePtr: network.getNodes()) {
		int nodeId = nodePtr->getNodeId();
		eventManager.addEvent(std::shared_ptr<Event>(
								new MessageToNodeEvent(
									std::shared_ptr<Message>(new NewBlockIdMessage(_genesisBlockId)),
									nodeId, -1, 0
								)
							 ));
	}

	LOG(INFO) << "[GenesisBlockEvent added to all nodes]";
}

void scheduleNextBlock(EventManager& eventManager, uint64_t _firstBlockInterval,
					   std::shared_ptr<Node> _firstBlockProducer, int _genesisBlockId) {
	int nodeId = _firstBlockProducer->getNodeId();

	eventManager.addEvent(std::shared_ptr<Event>(
								new MessageToNodeEvent(
									std::shared_ptr<Message>(new NewBlockMinedMessage()),
									nodeId, nodeId, _firstBlockInterval
								)
						  ));

	LOG(INFO) << "[Block 1 added to Node: " << nodeId << " at tickstamp: " << _firstBlockInterval << "]";
}

void scheduleBlockProduction(std::shared_ptr<BlockchainManagementModel> _blockchainManagementModel,
							 const Network& _network, std::shared_ptr<BlockCache> _blockCache,
							 EventManager& eventManager) {
	std::shared_ptr<Block> genesisBlock = _blockchainManagementModel->createGenesisBlock();
	_blockCache->insert(genesisBlock);

	sendGenesisBlockToAllNodes(_network, genesisBlock->getBlockId(), eventManager);

	uint64_t firstBlockInterval = _blockchainManagementModel->getNextBlockTime();
	std::shared_ptr<Node> firstBlockProducer = _blockchainManagementModel->getNextBlockProducer();

	scheduleNextBlock(eventManager, firstBlockInterval, firstBlockProducer, genesisBlock->getBlockId());
}

#endif /*INITIALIZATIONS_H_*/
