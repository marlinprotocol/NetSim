#include <memory>

#include "GlobalOrchestration.h"
#include "../../../core/EventManagement/Event/EventTypes/MessageToNodeEvent.h"

void GlobalOrchestration::sendBlockToAllNodes(Network& network, int _blockId, EventManager& eventManager) {
	for(auto nodePtr: network.getNodes()) {
		int nodeId = nodePtr->getNodeId();
		eventManager.addEvent(std::shared_ptr<Event>(
								new MessageToNodeEvent(
									std::shared_ptr<Message>(new NewBlockIdMessage(_blockId)),
									nodeId, -1, 0
								)
							 ));
	}

	LOG(INFO) << "[GenesisBlockEvent added to all nodes]";
}

void GlobalOrchestration::scheduleFirstBlock(const std::shared_ptr<Block> &genesisBlock,
						EventManager &eventManager) {
	scheduleNextBlock(&eventManager);
}

void GlobalOrchestration::scheduleBlockProduction(Network& _network, std::shared_ptr<BlockCache> _blockCache,
		 EventManager& eventManager) {
	std::shared_ptr<Block> genesisBlock = createGenesisBlock();
	_blockCache->insert(genesisBlock);

	sendBlockToAllNodes(_network, genesisBlock->getBlockId(), eventManager);

	scheduleFirstBlock(genesisBlock, eventManager);
}
