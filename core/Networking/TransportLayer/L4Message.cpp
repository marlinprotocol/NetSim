#include "L4Message.h"

L4Message::L4Message(std::shared_ptr<Message> _payload, bool _isReply, std::shared_ptr<L4Protocol> _l4Protocol, L4Address _src, L4Address _dest) :
		messageId(-1), payload(_payload), isReply(_isReply), l4Protocol(_l4Protocol), src(_src), dest(_dest) {}

L4Message::L4Message(std::shared_ptr<Message> _payload, bool _isReply, std::shared_ptr<L4Protocol> _l4Protocol, L4Address _src, L4Address _dest, uint64_t _messageId) :
		messageId(_messageId), payload(_payload), isReply(_isReply), l4Protocol(_l4Protocol), src(_src), dest(_dest) {}

L4Message::~L4Message() {}

std::shared_ptr<Message> L4Message::getPayload() {
	return payload;
}

L4Address L4Message::getDest() {
	return dest;
}

void L4Message::setDest(L4Address _dest) {
	dest = _dest;
}

bool L4Message::isIsReply() {
	return isReply;
}

void L4Message::setIsReply(bool _isReply) {
	isReply = _isReply;
}

std::shared_ptr<L4Protocol> L4Message::getL4Protocol() {
	return l4Protocol;
}

void L4Message::setL4Protocol(std::shared_ptr<L4Protocol> _l4Protocol) {
	l4Protocol = _l4Protocol;
}

int L4Message::getMessageId() {
	return messageId;
}

void L4Message::setMessageId(int _messageId) {
	messageId = _messageId;
}

L4Address L4Message::getSrc() {
	return src;
}

void L4Message::setSrc(L4Address _src) {
	src = _src;
}
