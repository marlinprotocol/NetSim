#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_

#include <memory>

class L4Address;
class L4Protocol;
class Message;

class L4Message {
protected:
	int messageId;
	std::shared_ptr<Message> payload;
	bool isReply;
	L4Protocol l4Protocol;
	L4Address src;
	L4Address dest;

public:
	L4Message(int _messageId, std::shared_ptr<Message> _payload, bool _isReply, L4Protocol _l4Protocol, L4Address _src, L4Address _dest);
	std::shared_ptr<Message> getPayload();
	L4Address getDest() const;
	void setDest(L4Address dest);
	bool isIsReply() const;
	void setIsReply(bool isReply);
	L4Protocol getL4Protocol() const;
	void setL4Protocol(L4Protocol l4Protocol);
	int getMessageId() const;
	void setMessageId(int messageId);
	L4Address getSrc() const;
	void setSrc(L4Address src);
	long long getSize() = 0;
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4MESSAGE_H_ */
