#ifndef CORE_NETWORKING_NETWORKMESSAGE_H_
#define CORE_NETWORKING_NETWORKMESSAGE_H_

#include <memory>

#include "NetworkProtocol.h"
#include "../Network/Node/NodeId.h"

class Message;

class NetworkMessage {
private:
	std::shared_ptr<Message> payload;
	NodeId sender;
	NodeId receiver;
	NetworkProtocol networkProtocol;

public:
	NetworkMessage(NodeId _sender, NodeId _receiver, std::shared_ptr<Message> _payload, NetworkProtocol _networkProtocol);
	std::shared_ptr<Message> getPayload();
	NetworkProtocol getNetworkProtocol();
	NodeId getReceiver();
	NodeId getSender();
};

#endif /* CORE_NETWORKING_NETWORKMESSAGE_H_ */
