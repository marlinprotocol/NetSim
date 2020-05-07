#include <cmath>

#include "TCPMessage.h"
#include "L4Message.h"
#include "../NetworkLayer/IPv4Message.h"
#include "../../Network/Messages/Message.h"

TCPMessage::TCPMessage(int _messageId, std::shared_ptr<Message> _payload, bool _isReply, L4Protocol _l4Protocol, L4Address _src, L4Address _dest, long long _seqNum) :
		L4Message(_messageId, _payload, _isReply, _l4Protocol, _src, _dest), seqNum(_seqNum) {
	int maxPayloadPerSegment = IPv4Message::MTU_SIZE - IPv4Message::HEADER_SIZE - TCPMessage::HEADER_SIZE;
	numSegments = ceil((double) _payload->getSize() / maxPayloadPerSegment);
}

long long TCPMessage::getSize() {
	return HEADER_SIZE * numSegments + payload->getSize();
}
