#ifndef INITIALIZATIONS_H_
#define INITIALIZATIONS_H_

#include <memory>

#include "./Logger/easylogging.h"
#include "../core/EventManagement/EventManager/EventManager.h"
#include "../core/Network/Network.h"
#include "../models/BlockchainManagementModels/BitcoinModel.h"

void sendGenesisBlockToAllNodes(const Network& network, int _genesisBlockId, EventManager& eventManager);

void scheduleNextBlock(EventManager& eventManager,
					   const std::shared_ptr<BlockchainManagementModel> &_blockchainManagementModel,
					   int _genesisBlockId);

void scheduleFirstBlock(const std::shared_ptr<BlockchainManagementModel> &_blockchainManagementModel,
						const std::shared_ptr<Block> &genesisBlock,
						EventManager &eventManager);

void scheduleBlockProduction(std::shared_ptr<BlockchainManagementModel> _blockchainManagementModel,
							 const Network& _network, std::shared_ptr<BlockCache> _blockCache,
							 EventManager& eventManager);

#endif /*INITIALIZATIONS_H_*/
