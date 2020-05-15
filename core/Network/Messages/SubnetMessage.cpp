#include "SubnetMessage.h"
#include "MessageType.h"
#include "../../Networking/NetworkLayer/NetworkMessage.h"

SubnetMessage::SubnetMessage(SubnetMessageType _subnetMessageType) :
	subnetMessageType(_subnetMessageType), transferProgress(nullptr), Message(MessageType::SUBNET_MSG) {
	assert(_subnetMessageType != SubnetMessageType::MESSAGE_RECVD);
}

SubnetMessage::SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<TransferProgress> _transferProgress) :
	subnetMessageType(_subnetMessageType), transferProgress(_transferProgress), Message(MessageType::SUBNET_MSG) {
	assert(_subnetMessageType != SubnetMessageType::BANDWIDTH_REALLOC);
}

SubnetMessage::SubnetMessage(SubnetMessageType _subnetMessageType, std::shared_ptr<NetworkMessage> _message) :
	subnetMessageType(_subnetMessageType), message(_message), Message(MessageType::SUBNET_MSG) {
	assert(_subnetMessageType != SubnetMessageType::FWD_TO_RECEIVER);
}
