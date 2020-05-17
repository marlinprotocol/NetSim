#ifndef CORE_NETWORKING_TRANSPORTLAYER_TCPMESSAGE_H_
#define CORE_NETWORKING_TRANSPORTLAYER_TCPMESSAGE_H_

#include "L4Message.h"

class TCPMessage : public L4Message {
private:
	long long seqNum;
	long long numSegments;

public:
	const static int HEADER_SIZE = 20;

	TCPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, long long _seqNum);
	TCPMessage(std::shared_ptr<Message> _payload, bool _isReply, L4Address _src, L4Address _dest, long long _seqNum, uint64_t _messageId);
	long long getSize();
	long long getSeqNum();
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_TCPMESSAGE_H_ */
