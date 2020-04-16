#ifndef MINER_H_
#define MINER_H_

#include <set>

#include "./Node.h"
#include "../../../helpers/Logger/easylogging.h"

class Miner : public Node {
private:
	int miningEventId; // default: -1 = not mining
	long long hashpower;
	double difficulty;
	int parentBlockMiningOn;
	std::set<int> receivedBlocks;

public:
	Miner(int _nodeId, bool _isAlive, int _region, 
		  std::shared_ptr<BlockCache> _blockCache, long long _hashpower, double _difficulty);
	long long getHashPower();
	bool setDifficulty(double _difficulty);
	double getDifficulty();
	double getLambda();
	void onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
							 std::vector<std::shared_ptr<Event>>& _newEvents);
	void onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message,
								std::shared_ptr<BlockCache> _blockCache,
								std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick);
};

#endif /*MINER_H_*/
