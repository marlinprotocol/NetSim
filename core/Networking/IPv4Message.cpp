#include <cmath>

#include "./IPv4Message.h"
#include "./NetworkProtocol.h"
#include "../Network/Messages/Message.h"

IPv4Message::IPv4Message(NodeId _receiver, NodeId _sender, std::shared_ptr<Message> _payload) :
	NetworkMessage(_receiver, _sender, _payload, NetworkProtocol::IPv4) {
	numFragments = (int) ceil( (double)_payload->getSize() / (double)(MTU_SIZE - HEADER_SIZE) );
	size = _payload->getSize() + numFragments * HEADER_SIZE;
}

long long IPv4Message::getSize() {
	return size;
}

int IPv4Message::getNumFragments() {
	return numFragments;
}
