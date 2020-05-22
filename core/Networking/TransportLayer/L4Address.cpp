#include <functional>
#include <string>

#include "L4Address.h"

L4Address::L4Address(NodeId _nodeId, short _port) : l3Address(L3Address(_nodeId)), port(_port) {}

L4Address::L4Address(L3Address _l3Address, short _port) : l3Address(_l3Address), port(_port) {}

bool L4Address::operator==(const L4Address &other) const {
	return (l3Address == other.getL3Address() && port == other.getPort());
}

L3Address L4Address::getL3Address() const {
	return l3Address;
}

void L4Address::setL3Address(L3Address _l3Address) {
	l3Address = _l3Address;
}

short L4Address::getPort() const {
	return port;
}

void L4Address::setPort(short _port) {
	port = _port;
}

int L4Address::getSize() {
	return l3Address.getSize() + sizeof(short);
}

