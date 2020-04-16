#ifndef BLOCKCHAINMGMTMODEL_H_
#define BLOCKCHAINMGMTMODEL_H_

#include <memory>

#include "../../../core/Blockchain/Block/Block.h"
#include "../../../core/EventManagement/EventManager/EventManager.h"
#include "../../../core/Network/Network.h"
#include "../../../core/Network/Node/Node.h"
#include "../../../helpers/Logger/easylogging.h"

class GlobalOrchestration {
public:
	virtual ~GlobalOrchestration() {}
	virtual std::shared_ptr<Block> createGenesisBlock() = 0;
	virtual uint64_t getNextBlockTime() = 0;
	virtual std::shared_ptr<Node> getNextBlockProducer() = 0;
	virtual int getNextBlockProducerId() = 0;
	virtual void scheduleNextBlock(EventManager* eventManager) = 0;

	void sendBlockToAllNodes(Network& network, int _blockId, EventManager& eventManager);
	void scheduleFirstBlock(const std::shared_ptr<Block> &genesisBlock, EventManager &eventManager);
	void scheduleBlockProduction(Network& _network, std::shared_ptr<BlockCache> _blockCache,
								 EventManager& eventManager);
};

#endif /*BLOCKCHAINMGMTMODEL_H_*/
