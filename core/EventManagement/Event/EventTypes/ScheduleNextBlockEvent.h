#ifndef SCHEDULENEXTBLOCKEVENT_H_
#define SCHEDULENEXTBLOCKEVENT_H_

#include <memory>

#include "../Event.h"
#include "../../../Network/Messages/Message.h"
#include "../../../Network/Messages/MessageType.h"

class ScheduleNextBlockEvent : public Event {
public: 
	ScheduleNextBlockEvent() : Event(0, EventType::SCHEDULE_NEXT_BLOCK) {};

	bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
				 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(DEBUG) << "[" << std::setw(35) << std::left << "ScheduleNextBlockEvent::execute]";
		return true;
	};

	bool execute(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(FATAL) << "[" << std::setw(35) << std::left << "ScheduleNextBlockEvent::execute][call without block cache not allowed]";
		return true;
	}
};

#endif /*SCHEDULENEXTBLOCKEVENT_H_*/
