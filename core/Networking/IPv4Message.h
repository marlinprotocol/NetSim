#ifndef CORE_NETWORKING_IPV4MESSAGE_H_
#define CORE_NETWORKING_IPV4MESSAGE_H_

#include "../Network/Node/NodeId.h"

class Message;

class IPv4Message {
private:
	int HEADER_SIZE = 20;
	int MTU_SIZE = 1500;
	int numFragments = 1;
	long long size = 0;

public:
	IPv4Message(NodeId receiver, NodeId sender, Message payload);
	long long getSize();
	int getNumFragments();
};

#endif /* CORE_NETWORKING_IPV4MESSAGE_H_ */
