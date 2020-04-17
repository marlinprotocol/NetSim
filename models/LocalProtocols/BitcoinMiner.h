#ifndef BITCOINMINER_H_
#define BITCOINMINER_H_

#include <memory>
#include <string>
#include <vector>

#include "Protocol.h"
#include "../../core/Blockchain/Blockchain.h"
#include "../../core/EventManagement/Event/Event.h"
#include "../../core/Network/Messages/Message.h"
#include "../../core/Network/Messages/NewBlockIdMessage.h"
#include "../../core/Network/Messages/NewBlockMinedMessage.h"
#include "../../core/Networking/RoutingTable.h"

class Node;

class BitcoinMiner : public Protocol {
private:
	int miningEventId; // default: -1 = not mining
	long long hashpower;
	double difficulty;
	int parentBlockMiningOn;
	std::set<int> receivedBlocks;
	std::shared_ptr<Node> parentNode;

public:
	BitcoinMiner(std::shared_ptr<Node> _parentNode, long long _hashpower, double _difficulty);
	long long getHashPower();
	bool setDifficulty(double _difficulty);
	std::string getProtocolType() {return "BITCOINMINER";};
	double getDifficulty();
	double getLambda();
	void onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
							 std::vector<std::shared_ptr<Event>>& _newEvents);
	void onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message,
								std::shared_ptr<BlockCache> _blockCache,
								std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick);
};

#endif /*BITCOINMINER_H_*/
