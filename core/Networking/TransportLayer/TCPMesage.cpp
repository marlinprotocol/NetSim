#include <cmath>

#include "TCPMessage.h"
#include "L4Message.h"
#include "L4Protocol.h"
#include "../NetworkLayer/IPv4Message.h"
#include "../../Network/Messages/Message.h"

TCPMessage::TCPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, long long _seqNum) :
		L4Message(_payload, _isReply, l4TCP, _src, _dest), seqNum(_seqNum) {
	int maxPayloadPerSegment = IPv4Message::MTU_SIZE - IPv4Message::HEADER_SIZE - TCPMessage::HEADER_SIZE;
	numSegments = ceil((double) _payload->getSize() / maxPayloadPerSegment);
}

long long TCPMessage::getSize() {
	return HEADER_SIZE * numSegments + payload->getSize();
}

long long TCPMessage::getSeqNum() {
	return seqNum;
}
