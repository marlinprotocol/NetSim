#ifndef CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_
#define CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_

#include "NetworkMessage.h"

class IPv4Message : NetworkMessage {
private:
	int numFragments = 1;
	long long size = 0;

public:
	static int HEADER_SIZE = 20;
	static int MTU_SIZE = 1500;

	IPv4Message(NodeId receiver, NodeId sender, std::shared_ptr<Message> payload);
	long long getSize();
	int getNumFragments();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_ */
