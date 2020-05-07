#include "UDPMessage.h"
#include "L4Message.h"
#include "../../Network/Messages/Message.h"

UDPMessage::UDPMessage(int _messageId, std::shared_ptr<Message> _payload, bool _isReply, L4Protocol _l4Protocol, L4Address _src, L4Address _dest) :
		L4Message(_messageId, _payload, _isReply, _l4Protocol, _src, _dest) {}

long long UDPMessage::getSize() {
	return HEADER_SIZE + payload->getSize();
}
