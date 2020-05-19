#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKMESSAGE_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKMESSAGE_H_

#include <memory>

#include "./NetworkProtocol.h"
#include "../../Network/Node/NodeId.h"

class L4Message;

class NetworkMessage {
private:
	std::shared_ptr<L4Message> payload;
	NodeId sender;
	NodeId receiver;
	NetworkProtocol networkProtocol;

public:
	NetworkMessage();
	NetworkMessage(NodeId _sender, NodeId _receiver, std::shared_ptr<L4Message> _payload, NetworkProtocol _networkProtocol);
	virtual ~NetworkMessage();
	std::shared_ptr<L4Message> getPayload();
	NetworkProtocol getNetworkProtocol();
	NodeId getReceiver();
	NodeId getSender();
	virtual long long getSize() = 0;
	virtual int getNumFragments() = 0;
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKMESSAGE_H_ */
