#include <memory>

#include "./Miner.h"
#include "../Messages/NewBlockMinedMessage.h"
#include "../../Blockchain/Block/PoWBlock.h"
#include "../../EventManagement/Event/EventTypes/MessageToNodeEvent.h"
#include "../../EventManagement/Event/EventTypes/ScheduleNextBlockEvent.h"

Miner::Miner(int _nodeId, bool _isAlive, int _region, 
			 std::shared_ptr<BlockCache> _blockCache, long long _hashpower, double _difficulty)
	  : Node(_nodeId, _isAlive, _region, _blockCache), parentBlockMiningOn(0),
		miningEventId(-1), hashpower(_hashpower), difficulty(_difficulty) {
}

long long Miner::getHashPower() {
	return hashpower;
}

bool Miner::setDifficulty(double _difficulty) {
	difficulty = _difficulty;
	return true;
}

double Miner::getDifficulty() {
	return difficulty;
}

double Miner::getLambda() {
	return (double) hashpower/difficulty;
}

void Miner::onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
								std::vector<std::shared_ptr<Event>>& _newEvents) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockIdMessage]"
			   << "[NodeId:" << std::setw(6) << std::right << std::to_string(getNodeId()) << "]";

	int prevBlockchainHeight = blockchain.getBlockchainHeight();

	int newBlockHeight = _blockCache->getBlockById(_message->getBlockId())->getBlockHeight();

	if(newBlockHeight <= prevBlockchainHeight + 1) {
		blockchain.addBlock(newBlockHeight, _message->getBlockId());

		int newBlockchainHeight = blockchain.getBlockchainHeight();

		LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockIdMessage]"
				   << "[PrevHt:" << std::setw(6) << std::right << std::to_string(prevBlockchainHeight) << "]"
				   << "[BlckHt:" << std::setw(6) << std::right << std::to_string(newBlockHeight) << "]"
				   << "[NewHt:" << std::setw(6) << std::right << std::to_string(newBlockchainHeight) << "]";

		if(newBlockHeight == prevBlockchainHeight + 1)
			parentBlockMiningOn = _message->getBlockId();
	}
}

void Miner::onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message, std::shared_ptr<BlockCache> _blockCache,
								   std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockMinedMessage]"
			   << "[NodeId:" << std::setw(6) << std::right << std::to_string(getNodeId()) << "]";

	auto parentBlockId = parentBlockMiningOn;
	int parentBlockHeight = _blockCache->getBlockById(parentBlockId)->getBlockHeight();

	int latestBlockHeightInStore = blockchain.getBlockchainHeight();

//	if(parentBlockHeight != latestBlockHeightInStore) {
//		LOG(DEBUG) << "[Miner::onNewBlockMinedMessage][ERROR][parentBlockHeight != latestBlockHeightInStore]";
//		return;
//	}

	int newBlockHeight = parentBlockHeight + 1;

	auto newBlock = std::shared_ptr<Block>(new PoWBlock(parentBlockId, getNodeId(), newBlockHeight, _currentTick));

	blockchain.addBlock(newBlockHeight, newBlock->getBlockId());
	blockCache->insert(newBlock);

	parentBlockMiningOn = newBlock->getBlockId();

	_newEvents.push_back(std::make_shared<ScheduleNextBlockEvent>(ScheduleNextBlockEvent()));

	for(int i=0; i<15; i++) {
		_newEvents.push_back(std::make_shared<MessageToNodeEvent>( MessageToNodeEvent(std::shared_ptr<Message>(new NewBlockIdMessage(newBlock->getBlockId())), i, getNodeId(), 0) ));
	}
}
