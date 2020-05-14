#include "L4Message.h"

L4Message::L4Message(std::shared_ptr<Message> _payload, bool _isReply, L4Protocol _l4Protocol, L4Address _src, L4Address _dest) :
		messageId(-1), payload(_payload), isReply(_isReply), l4Protocol(_l4Protocol), src(_src), dest(_dest) {}

inline L4Address L4Message::getDest() const {
	return dest;
}

inline void L4Message::setDest(L4Address _dest) {
	dest = _dest;
}

inline bool L4Message::isIsReply() const {
	return isReply;
}

inline void L4Message::setIsReply(bool _isReply) {
	isReply = _isReply;
}

inline L4Protocol L4Message::getL4Protocol() const {
	return l4Protocol;
}

inline void L4Message::setL4Protocol(L4Protocol _l4Protocol) {
	l4Protocol = _l4Protocol;
}

inline int L4Message::getMessageId() const {
	return messageId;
}

inline void L4Message::setMessageId(int _messageId) {
	messageId = _messageId;
}

inline L4Address L4Message::getSrc() const {
	return src;
}

inline void L4Message::setSrc(L4Address _src) {
	src = _src;
}
