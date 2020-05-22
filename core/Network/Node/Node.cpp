#include "./Node.h"
#include "../../Networking/Bandwidth.h"
#include "../../Networking/NetworkLayer/NetworkLayer.h"
#include "../../../models/Networking/BitcoinRoutingTable.h"

Node::Node(int _nodeId, bool _isAlive, int _region, std::shared_ptr<BlockCache> _blockCache, std::shared_ptr<Subnet> _subnet)
	 : nodeId(_nodeId), isAlive(_isAlive), region(_region), blockCache(_blockCache),
	   networkLayer(std::make_shared<NetworkLayer>(NetworkLayer(5000, 5000, _subnet, _nodeId))),
	   blockchain(std::make_shared<Blockchain>(Blockchain(std::const_pointer_cast<const BlockCache>(_blockCache)))),
	   routingTable(std::make_shared<BitcoinRoutingTable>(BitcoinRoutingTable(_nodeId))){}

Node::Node(int _nodeId, double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet, std::string _countryCode)
	 : nodeId(_nodeId), isAlive(true), region(0), blockCache(nullptr), countryCode(_countryCode),
	   networkLayer(std::make_shared<NetworkLayer>(NetworkLayer(_downloadBandwidth, _uploadBandwidth, _subnet, _nodeId))),
	   blockchain(std::make_shared<Blockchain>(nullptr)),
   	   routingTable(std::make_shared<BitcoinRoutingTable>(BitcoinRoutingTable(_nodeId))){}

int Node::getRegion() const {
	return region;
}

int Node::getNodeId() const {
	return nodeId;
}

std::string Node::getCountryCode() {
	return countryCode;
}

std::shared_ptr<Blockchain> Node::getBlockchain() {
	return blockchain;
}

std::shared_ptr<BlockCache> Node::getBlockCache() {
	return blockCache;
}

bool Node::addProtocol(std::shared_ptr<Protocol> protocol) {
	protocols.push_back(protocol);
	return true;
}

std::vector<std::shared_ptr<Protocol>> Node::getProtocols() {
	return protocols;
}

std::shared_ptr<Bandwidth> Node::getCurrentBandwidth() {
	return networkLayer->getCurrentBandwidth();
}

std::shared_ptr<Bandwidth> Node::getMaxBandwidth() {
	return networkLayer->getMaxBandwidth();
}

std::shared_ptr<RoutingTable> Node::getRoutingTable() {
	return routingTable;
}

std::shared_ptr<NetworkLayer> Node::getNetworkLayer() {
	return networkLayer;
}
