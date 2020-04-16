#ifndef EVENT_H_
#define EVENT_H_

#include "./EventTypes/EventType.h"
#include "../../Network/Network.h"
#include "../../../helpers/Logger/easylogging.h"

class EventQueue;

class Event {
private:
	uint64_t durationInTicks;
	EventType eventType;

public:
	Event(uint64_t _durationInTicks, EventType _eventType);
	uint64_t getDurationInTicks();
	virtual bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
						 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) = 0;
	virtual ~Event() {}
	EventType getEventType();
};

#endif /*EVENT_H_*/
