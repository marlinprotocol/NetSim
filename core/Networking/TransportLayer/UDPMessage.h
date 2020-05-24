#ifndef CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_
#define CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_

#include <memory>

#include "L4Message.h"

class L4Protocol;

extern std::shared_ptr<L4Protocol> l4UDP;

class UDPMessage : public L4Message {
private:
	int HEADER_SIZE = 8;

public:
	UDPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest);
	UDPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, uint64_t _messageId);
	long long getSize();
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_ */
