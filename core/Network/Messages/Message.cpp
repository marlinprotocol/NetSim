#include "./Message.h"

Message::Message(MessageType _messageType) : messageType(_messageType) {}

MessageType Message::getMessageType() {
	return messageType;
}

long long Message::getSize() { // TODO:temporary
	return 0;
}
