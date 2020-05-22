#include "./Message.h"

Message::Message(MessageType _messageType) : messageType(_messageType), size(0) {}

MessageType Message::getMessageType() {
	return messageType;
}

void Message::setSize(int _size) {
	size = _size;
}

long long Message::getSize() {
	return size;
}
