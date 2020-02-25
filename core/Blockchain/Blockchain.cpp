#include "./Blockchain.h"
#include "../../helpers/Logger/easylogging.h"

Blockchain::Blockchain(std::shared_ptr<const BlockCache> _blockCache) {
	blockCache = _blockCache;
}

int Blockchain::getBlockchainHeight() {
	return blockchain.getTotalInsertions() - 1;
}

std::vector<int> Blockchain::getLatestBlockIds() {
	int blockchainHeight = getBlockchainHeight();
	return getBlockIdsAtHeight(blockchainHeight);
}

int Blockchain::oldestBlockHeightInCache() {
	int indexOfEarliestInsertion = blockchain.getOldestItemIndex();

	if(indexOfEarliestInsertion == -1) {
		return -1;
	}

	const std::vector<int>& blockIds = blockchain.getItemAtIndex(indexOfEarliestInsertion);

	return (*blockCache).getBlockById(blockIds[0])->getBlockHeight();
}

int Blockchain::getBlockchainStorageSize() {
	return blockchain.getQueueSize();
}

bool Blockchain::hasBlock(int blockHeight, int blockId) {
	if(blockHeight < oldestBlockHeightInCache() || blockHeight > getBlockchainHeight()) 
		return false;

	const std::vector<int>& blockIds = blockchain.getItemAtIndex(blockHeight % blockchain.getQueueSize());
	return std::find(blockIds.begin(), blockIds.end(), blockId) != blockIds.end();
}

bool Blockchain::addBlockAtHeight(int blockId, int blockHeight) {
	std::vector<int>& blockIds = blockchain.getItemAtIndex(blockHeight % blockchain.getQueueSize());
	blockIds.push_back(blockId);

	return true;
}

bool Blockchain::addBlock(int newBlockHeight, int newBlockId) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "Blockchain::addBlock]"
			   << "[Height:" << std::setw(6) << std::right << std::to_string(newBlockHeight) << "]"
			   << "[Id:" << std::setw(8) << std::right << std::to_string(newBlockId) << "]";


	if(newBlockHeight < oldestBlockHeightInCache()) {
		LOG(DEBUG) << "Received old block at height " << newBlockHeight
			       << " while oldest block height in cache is " << oldestBlockHeightInCache();
		return false;
	}
	else if(newBlockHeight <= getBlockchainHeight()) {
		if(hasBlock(newBlockHeight, newBlockId)) {
			return false;
		}
		else {
			addBlockAtHeight(newBlockHeight, newBlockId);
		}
	}
	else if(newBlockHeight == getBlockchainHeight() + 1) {
		std::vector<int> newBlockListAtTip;
		newBlockListAtTip.push_back(newBlockId);
		blockchain.insert(newBlockListAtTip);

		// remove its mining event
	}
	else {

	}

	return true;
}

std::vector<int> Blockchain::getBlockIdsAtHeight(int blockHeight) {
	if (blockHeight<0) {
		return std::vector<int>();
	}

	return blockchain.getItemAtIndex(blockHeight % blockchain.getQueueSize());
}