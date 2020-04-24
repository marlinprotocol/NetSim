#ifndef CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_
#define CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_

#include "NetworkMessage.h"

class IPv4Message : NetworkMessage {
private:
	int HEADER_SIZE = 20;
	int MTU_SIZE = 1500;
	int numFragments = 1;
	long long size = 0;

public:
	IPv4Message(NodeId receiver, NodeId sender, std::shared_ptr<Message> payload);
	long long getSize();
	int getNumFragments();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_ */
