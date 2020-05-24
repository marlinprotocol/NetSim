#include "UDPMessage.h"
#include "L4Message.h"
#include "L4Protocol.h"
#include "../../Network/Messages/Message.h"

std::shared_ptr<L4Protocol> l4UDP = std::make_shared<L4Protocol>(L4ProtocolType::UDP, false, false);

//L4Protocol l4UDP(L4ProtocolType::UDP, false, false);

UDPMessage::UDPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest)
		   : L4Message(_payload, _isReply, l4UDP, _src, _dest) {}

UDPMessage::UDPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, uint64_t _messageId)
		   : L4Message(_payload, _isReply, l4UDP, _src, _dest, _messageId) {}

long long UDPMessage::getSize() {
	return HEADER_SIZE + payload->getSize();
}
