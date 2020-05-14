#ifndef CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_
#define CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_

#include <memory>

#include "Message.h"

class TransferProgress;

enum class SubnetMessageType {MESSAGE_RECVD, BANDWIDTH_REALLOC};

class SubnetMessage : public Message {
private:
	SubnetMessageType subnetMessageType;
	std::shared_ptr<TransferProgress> transferProgress;

public:
	SubnetMessage(SubnetMessageType _subnetMessageType);
	SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<TransferProgress> _transferProgress);
	std::string getType();
};

#endif /* CORE_NETWORK_MESSAGES_SUBNETMESSAGE_H_ */
