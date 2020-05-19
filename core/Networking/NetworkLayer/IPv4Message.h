#ifndef CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_
#define CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_

#include "NetworkMessage.h"

class L4Message;

class IPv4Message : public NetworkMessage {
private:
	int numFragments = 1;
	long long size = 0;

public:
	const static int HEADER_SIZE = 20;
	const static int MTU_SIZE = 1500;

	IPv4Message();
	IPv4Message(NodeId _sender, NodeId _receiver, std::shared_ptr<L4Message> payload);
	long long getSize();
	int getNumFragments();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_IPV4MESSAGE_H_ */
