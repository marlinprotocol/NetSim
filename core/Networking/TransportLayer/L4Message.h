#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_

#include <memory>

#include "L4Address.h"
#include "L4Protocol.h"

class Message;

class L4Message {
protected:
	uint64_t messageId;
	std::shared_ptr<Message> payload;
	bool isReply;
	std::shared_ptr<L4Protocol> l4Protocol;
	L4Address src;
	L4Address dest;

public:
	L4Message(std::shared_ptr<Message> _payload, bool _isReply, std::shared_ptr<L4Protocol> _l4Protocol, L4Address _src, L4Address _dest);
	L4Message(std::shared_ptr<Message> _payload, bool _isReply, std::shared_ptr<L4Protocol> _l4Protocol, L4Address _src, L4Address _dest, uint64_t _messageId);
	virtual ~L4Message() = 0;
	std::shared_ptr<Message> getPayload();
	L4Address getDest();
	void setDest(L4Address dest);
	bool isIsReply();
	void setIsReply(bool isReply);
	std::shared_ptr<L4Protocol> getL4Protocol();
	void setL4Protocol(std::shared_ptr<L4Protocol> l4Protocol);
	int getMessageId();
	void setMessageId(int messageId);
	L4Address getSrc();
	void setSrc(L4Address src);
	virtual long long getSize() = 0;
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_ */
