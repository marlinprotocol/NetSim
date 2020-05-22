#include "./NetworkMessage.h"

NetworkMessage::NetworkMessage() {
	// nenvbers knowingly left uninitialized to detect errors
}

NetworkMessage::NetworkMessage(NodeId _sender, NodeId _receiver, std::shared_ptr<L4Message> _payload, NetworkProtocol _networkProtocol) :
		sender(_sender), receiver(_receiver), payload(_payload), networkProtocol(_networkProtocol) {}

NetworkMessage::~NetworkMessage() {}

std::shared_ptr<L4Message> NetworkMessage::getPayload() {
	return payload;
}

NetworkProtocol NetworkMessage::getNetworkProtocol() {
	return networkProtocol;
}

NodeId NetworkMessage::getReceiver() {
	return receiver;
}

NodeId NetworkMessage::getSender() {
	return sender;
}
