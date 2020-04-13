#ifndef INITIALIZATIONS_H_
#define INITIALIZATIONS_H_

#include <memory>

#include "./Logger/easylogging.h"
#include "../core/Network/Network.h"
#include "../models/BlockchainManagementModels/BitcoinModel.h"

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

void scheduleNextBlock(EventManager& eventManager,
					   const std::shared_ptr<BlockchainManagementModel> &_blockchainManagementModel,
					   int _genesisBlockId) {
	uint64_t blockInterval = _blockchainManagementModel->getNextBlockTime();
	std::shared_ptr<Node> blockProducer = _blockchainManagementModel->getNextBlockProducer();

	int nodeId = blockProducer->getNodeId();

	eventManager.addEvent(std::shared_ptr<Event>(
								new MessageToNodeEvent(
									std::shared_ptr<Message>(new NewBlockMinedMessage()),
									nodeId, nodeId, blockInterval
								)
						  ));

	LOG(INFO) << "[Block 1 added to Node: " << nodeId << " at tickstamp: " << blockInterval << "]";
}

void scheduleFirstBlock(const std::shared_ptr<BlockchainManagementModel> &_blockchainManagementModel,
						const std::shared_ptr<Block> &genesisBlock,
						EventManager &eventManager) {
	scheduleNextBlock(eventManager, _blockchainManagementModel, genesisBlock->getBlockId());
}

void scheduleBlockProduction(std::shared_ptr<BlockchainManagementModel> _blockchainManagementModel,
							 const Network& _network, std::shared_ptr<BlockCache> _blockCache,
							 EventManager& eventManager) {
	std::shared_ptr<Block> genesisBlock = _blockchainManagementModel->createGenesisBlock();
	_blockCache->insert(genesisBlock);

	sendGenesisBlockToAllNodes(_network, genesisBlock->getBlockId(), eventManager);

	scheduleFirstBlock(_blockchainManagementModel, genesisBlock, eventManager);
}

#endif /*INITIALIZATIONS_H_*/
