#include "./Node.h"
#include "../../Networking/Bandwidth.h"
#include "../../../models/Networking/BitcoinRoutingTable.h"

Node::Node(int _nodeId, bool _isAlive, int _region, std::shared_ptr<BlockCache> _blockCache)
	 : nodeId(_nodeId), isAlive(_isAlive), region(_region), blockCache(_blockCache),
	          currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(5000, 5000))),
			  maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(5000, 5000))),
	 		  blockchain(std::make_shared<Blockchain>(Blockchain(std::const_pointer_cast<const BlockCache>(_blockCache)))),
			  routingTable(std::make_shared<BitcoinRoutingTable>(BitcoinRoutingTable(_nodeId))){}

Node::Node(int _nodeId, double _maxDownBandwidth, double _upDownBandwidth)
	 : nodeId(_nodeId), isAlive(true), region(0), blockCache(nullptr),
	          currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(_maxDownBandwidth, _upDownBandwidth))),
			  maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(_maxDownBandwidth, _upDownBandwidth))),
	 		  blockchain(std::make_shared<Blockchain>(nullptr)),
			  routingTable(std::make_shared<BitcoinRoutingTable>(BitcoinRoutingTable(_nodeId))){}

int Node::getRegion() const {
	return region;
}

int Node::getNodeId() const {
	return nodeId;
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
	return currentBandwidth;
}

std::shared_ptr<Bandwidth> Node::getMaxBandwidth() {
	return maxBandwidth;
}

std::shared_ptr<RoutingTable> Node::getRoutingTable() {
	return routingTable;
}
