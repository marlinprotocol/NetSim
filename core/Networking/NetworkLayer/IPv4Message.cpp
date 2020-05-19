#include "./IPv4Message.h"

#include <cmath>

#include "./NetworkProtocol.h"
#include "../TransportLayer/L4Message.h"

IPv4Message::IPv4Message() {}

IPv4Message::IPv4Message(NodeId _sender, NodeId _receiver, std::shared_ptr<L4Message> _payload) :
	NetworkMessage(_sender, _receiver, _payload, NetworkProtocol::IPv4) {
	numFragments = (int) ceil( (double)_payload->getSize() / (double)(MTU_SIZE - HEADER_SIZE) );
	size = _payload->getSize() + numFragments * HEADER_SIZE;
}

long long IPv4Message::getSize() {
	return size;
}

int IPv4Message::getNumFragments() {
	return numFragments;
}
