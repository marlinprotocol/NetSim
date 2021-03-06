#ifndef CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_
#define CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_

#include <memory>

#include "Message.h"

class NetworkMessage;
class TransferProgress;

enum class SubnetMessageType {MESSAGE_RECVD, BANDWIDTH_REALLOC, FWD_TO_RECEIVER, DISCONNECT, RECONNECT, CANCEL_TRANSMISSION};

class SubnetMessage : public Message {
private:
	SubnetMessageType subnetMessageType;
	std::shared_ptr<TransferProgress> transferProgress;
	std::shared_ptr<NetworkMessage> message;

public:
	SubnetMessage(SubnetMessageType _subnetMessageType);
	SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<TransferProgress> _transferProgress);
	SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<NetworkMessage> _message);
	std::shared_ptr<TransferProgress> getTransferProgress();
	std::shared_ptr<NetworkMessage> getNetworkMessage();
	SubnetMessageType getSubnetType();
	std::string getType();
};

#endif /* CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_ */
