#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <vector>

#include "../Messages/Message.h"
#include "../Messages/NewBlockIdMessage.h"
#include "../Messages/NewBlockMinedMessage.h"
#include "../../Blockchain/Blockchain.h"
#include "../../Networking/RoutingTable.h"
#include "../../../helpers/Logger/easylogging.h"

class Event;
class Protocol;

class Node {
private:
	int nodeId;
	bool isAlive;
	int region;
	std::shared_ptr<RoutingTable> routingTable;
	std::vector<std::shared_ptr<Protocol>> protocols;
	std::shared_ptr<Blockchain> blockchain;
	std::shared_ptr<BlockCache> blockCache;

public:
	Node(int _nodeId, bool _isAlive, int _region, 
		 std::shared_ptr<BlockCache> _blockCache);
	int getRegion() const;
	int getNodeId() const;
	std::shared_ptr<Blockchain> getBlockchain();
	std::shared_ptr<BlockCache> getBlockCache();
	bool addProtocol(std::shared_ptr<Protocol> protocol);
	std::vector<std::shared_ptr<Protocol>> getProtocols();
	std::shared_ptr<RoutingTable> getRoutingTable();
};

#endif /*NODE_H_*/
