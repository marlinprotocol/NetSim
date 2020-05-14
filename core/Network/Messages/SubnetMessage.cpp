#include "SubnetMessage.h"
#include "MessageType.h"

SubnetMessage::SubnetMessage(SubnetMessageType _subnetMessageType) :
	subnetMessageType(_subnetMessageType), transferProgress(nullptr), Message(MessageType::SUBNET_MSG) {
	assert(_subnetMessageType != SubnetMessageType::MESSAGE_RECVD);
}

SubnetMessage::SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<TransferProgress> _transferProgress) :
	subnetMessageType(_subnetMessageType), transferProgress(_transferProgress), Message(MessageType::SUBNET_MSG) {
	assert(_subnetMessageType != SubnetMessageType::BANDWIDTH_REALLOC);
}
