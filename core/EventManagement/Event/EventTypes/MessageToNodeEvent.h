#ifndef MESSAGETONODEEVENT_H_
#define MESSAGETONODEEVENT_H_

#include <memory>

#include "../Event.h"
#include "../../../Network/Messages/Message.h"
#include "../../../Network/Messages/MessageType.h"

class MessageToNodeEvent : public Event {
private:
	std::shared_ptr<Message> message;
	int forNodeId;
	int fromNodeId;

public: 
	MessageToNodeEvent(std::shared_ptr<Message> _message, int _forNodeId, int _fromNodeId,
					   long long _durationInTicks);
	bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
				 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick);
};

#endif /*MESSAGETONODEEVENT_H_*/
