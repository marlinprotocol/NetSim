#include <functional>

#include "L3Address.h"

L3Address::L3Address(NodeId _nodeId) : nodeId(_nodeId) {}

bool L3Address::operator==(const L3Address &other) const {
	return nodeId == other.nodeId;
}

int L3Address::getSize() {
	return 8; // to emulate IPv4 Address size
}
