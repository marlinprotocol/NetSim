#ifndef CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_
#define CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_

#include "L4Message.h"

class UDPMessage : public L4Message {
private:
	int HEADER_SIZE = 8;

public:
	UDPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest);
	long long getSize();
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_UDPMESSAGE_H_ */
