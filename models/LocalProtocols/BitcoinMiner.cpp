#include "BitcoinMiner.h"
#include "../../core/Blockchain/Block/PoWBlock.h"
#include "../../core/EventManagement/Event/EventTypes/MessageToNodeEvent.h"
#include "../../core/EventManagement/Event/EventTypes/ScheduleNextBlockEvent.h"
#include "../../core/Network/Messages/NewBlockMinedMessage.h"
#include "../../core/Network/Node/Node.h"

BitcoinMiner::BitcoinMiner(std::shared_ptr<Node> _parentNode, long long _hashpower, double _difficulty)
					      : parentNode(_parentNode), parentBlockMiningOn(0), miningEventId(-1), hashpower(_hashpower), difficulty(_difficulty) {
}

long long BitcoinMiner::getHashPower() {
	return hashpower;
}

bool BitcoinMiner::setDifficulty(double _difficulty) {
	difficulty = _difficulty;
	return true;
}

double BitcoinMiner::getDifficulty() {
	return difficulty;
}

double BitcoinMiner::getLambda() {
	return (double) hashpower/difficulty;
}

void BitcoinMiner::onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
									   std::vector<std::shared_ptr<Event>>& _newEvents) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockIdMessage]"
			   << "[NodeId:" << std::setw(6) << std::right << std::to_string(parentNode->getNodeId()) << "]";

	int prevBlockchainHeight = parentNode->getBlockchain()->getBlockchainHeight();

	int newBlockHeight = _blockCache->getBlockById(_message->getBlockId())->getBlockHeight();

	if(newBlockHeight <= prevBlockchainHeight + 1) {
		parentNode->getBlockchain()->addBlock(newBlockHeight, _message->getBlockId());

		int newBlockchainHeight = parentNode->getBlockchain()->getBlockchainHeight();

		LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockIdMessage]"
				   << "[PrevHt:" << std::setw(6) << std::right << std::to_string(prevBlockchainHeight) << "]"
				   << "[BlckHt:" << std::setw(6) << std::right << std::to_string(newBlockHeight) << "]"
				   << "[NewHt:" << std::setw(6) << std::right << std::to_string(newBlockchainHeight) << "]";

		if(newBlockHeight == prevBlockchainHeight + 1)
			parentBlockMiningOn = _message->getBlockId();
	}
}

void BitcoinMiner::onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message, std::shared_ptr<BlockCache> _blockCache,
								   	      std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "Miner::onNewBlockMinedMessage]"
			   << "[NodeId:" << std::setw(6) << std::right << std::to_string(parentNode->getNodeId()) << "]";

	auto parentBlockId = parentBlockMiningOn;
	int parentBlockHeight = _blockCache->getBlockById(parentBlockId)->getBlockHeight();

	int latestBlockHeightInStore = parentNode->getBlockchain()->getBlockchainHeight();

//	if(parentBlockHeight != latestBlockHeightInStore) {
//		LOG(DEBUG) << "[Miner::onNewBlockMinedMessage][ERROR][parentBlockHeight != latestBlockHeightInStore]";
//		return;
//	}

	int newBlockHeight = parentBlockHeight + 1;

	auto newBlock = std::shared_ptr<Block>(new PoWBlock(parentBlockId, parentNode->getNodeId(), newBlockHeight, _currentTick));

	parentNode->getBlockchain()->addBlock(newBlockHeight, newBlock->getBlockId());
	parentNode->getBlockCache()->insert(newBlock);

	parentBlockMiningOn = newBlock->getBlockId();

	_newEvents.push_back(std::make_shared<ScheduleNextBlockEvent>(ScheduleNextBlockEvent()));

	for(int i=0; i<15; i++) {
		_newEvents.push_back(std::make_shared<MessageToNodeEvent>( MessageToNodeEvent(std::shared_ptr<Message>(new NewBlockIdMessage(newBlock->getBlockId())), i, parentNode->getNodeId(), 0) ));
	}
}
