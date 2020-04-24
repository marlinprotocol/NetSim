#include <cmath>

#include "./IPv4Message.h"
#include "../Network/Messages/Message.h"

IPv4Message::IPv4Message(NodeId receiver, NodeId sender, Message payload) {
	numFragments = (int) ceil( (double)payload.getSize() / (double)(MTU_SIZE - HEADER_SIZE) );
	size = payload.getSize() + numFragments * HEADER_SIZE;
}

long long IPv4Message::getSize() {
	return size;
}

int IPv4Message::getNumFragments() {
	return numFragments;
}
