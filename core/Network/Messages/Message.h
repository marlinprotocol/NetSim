#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "./MessageType.h"
#include "../../../helpers/Logger/easylogging.h"

class Message {
private:
	MessageType messageType;
	int size;

public:
	Message(MessageType _messageType);
	virtual std::string getType() = 0;
	virtual ~Message() {};
	MessageType getMessageType();
	void setSize(int _size);
	long long getSize(); // TODO: make virtual
};

#endif /*MESSAGE_H_*/
