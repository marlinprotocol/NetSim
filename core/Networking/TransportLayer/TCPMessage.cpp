#include <cmath>

#include "TCPMessage.h"
#include "L4Message.h"
#include "L4Protocol.h"
#include "../NetworkLayer/IPv4Message.h"
#include "../../Network/Messages/Message.h"

std::shared_ptr<L4Protocol> l4TCP = std::make_shared<L4Protocol>(L4ProtocolType::TCP, true, true);

TCPMessage::TCPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, long long _seqNum)
		   : L4Message(_payload, _isReply, l4TCP, _src, _dest), seqNum(_seqNum) {
	int maxPayloadPerSegment = IPv4Message::MTU_SIZE - IPv4Message::HEADER_SIZE - TCPMessage::HEADER_SIZE;
	numSegments = ceil((double) _payload->getSize() / maxPayloadPerSegment);
}

TCPMessage::TCPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, long long _seqNum, uint64_t _messageId) :
		L4Message(_payload, _isReply, l4TCP, _src, _dest, _messageId), seqNum(_seqNum) {
	int maxPayloadPerSegment = IPv4Message::MTU_SIZE - IPv4Message::HEADER_SIZE - TCPMessage::HEADER_SIZE;
	numSegments = ceil((double) _payload->getSize() / maxPayloadPerSegment);
}

long long TCPMessage::getSize() {
	return HEADER_SIZE * numSegments + payload->getSize();
}

long long TCPMessage::getSeqNum() {
	return seqNum;
}
