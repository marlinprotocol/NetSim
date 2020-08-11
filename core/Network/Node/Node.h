#ifndef NODE_H_
#define NODE_H_

#include <memory>
#include <vector>

#include "NodeId.h"
#include "../Messages/Message.h"
#include "../Messages/NewBlockIdMessage.h"
#include "../Messages/NewBlockMinedMessage.h"
#include "../../Blockchain/Blockchain.h"
#include "../../Networking/RoutingTable.h"
#include "../../../helpers/Logger/easylogging.h"

class Bandwidth;
class Event;
class NetworkLayer;
class Protocol;
class Subnet;

class Node {
private:
	NodeId nodeId;
	bool isAlive;
	int region;
	int cityIdx;
	std::string countryCode;
	std::shared_ptr<RoutingTable> routingTable;
	std::vector<std::shared_ptr<Protocol>> protocols;
	std::shared_ptr<Blockchain> blockchain;
	std::shared_ptr<BlockCache> blockCache;
	std::shared_ptr<NetworkLayer> networkLayer;

public:
	Node(int _nodeId, bool _isAlive, int _region, int _cityIdx, std::shared_ptr<BlockCache> _blockCache,
		 std::shared_ptr<Subnet> _subnet, std::string _routingTable);
	Node(int _nodeId, double _maxDownBandwidth, double _upDownBandwidth, std::shared_ptr<Subnet> _subnet,
		 std::string _countryCode, std::string _routingTable);
	int getRegion() const;
	int getNodeId() const;
	int getCityIdx();
	std::string getCountryCode();
	std::shared_ptr<Blockchain> getBlockchain();
	std::shared_ptr<BlockCache> getBlockCache();
	bool addProtocol(std::shared_ptr<Protocol> protocol);
	std::vector<std::shared_ptr<Protocol>> getProtocols();
	std::shared_ptr<RoutingTable> getRoutingTable();
	std::shared_ptr<Bandwidth> getCurrentBandwidth();
	std::shared_ptr<Bandwidth> getMaxBandwidth();
	std::shared_ptr<NetworkLayer> getNetworkLayer();
};

#endif /*NODE_H_*/
