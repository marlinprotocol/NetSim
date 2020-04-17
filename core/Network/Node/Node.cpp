#include "./Node.h"

Node::Node(int _nodeId, bool _isAlive, int _region, 
		   std::shared_ptr<BlockCache> _blockCache) 
	 : nodeId(_nodeId), isAlive(_isAlive), region(_region), blockCache(_blockCache),
	 		  blockchain(std::make_shared<Blockchain>(Blockchain(std::const_pointer_cast<const BlockCache>(_blockCache)))) {}

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
