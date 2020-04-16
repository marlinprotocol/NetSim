#include "AsyncEvent.h"

int AsyncEvent::count = 0;

AsyncEvent::AsyncEvent(int _id) : id(_id), tickToExecOn(0) {}

AsyncEvent::AsyncEvent(std::shared_ptr<Event> _event, uint64_t _tickToExecOn) {
	event = _event;
	tickToExecOn = _tickToExecOn;
	id = count++;
}

bool AsyncEvent::operator<(const AsyncEvent& e) const { 
	if(tickToExecOn == e.tickToExecOn) return id < e.id;
	return tickToExecOn > e.tickToExecOn; 
} 

bool AsyncEvent::operator==(const AsyncEvent& e) const { 	
	return id == e.id; 
} 

long AsyncEvent::getTickToExecOn() const {
	return tickToExecOn;
}

bool AsyncEvent::execute(Network& _network,
						 std::shared_ptr<BlockCache> _blockCache,
						 std::vector<std::shared_ptr<Event>>& _newEvents,
						 uint64_t _currentTick) {
	LOG(DEBUG) << "[AsyncEvent::execute]";
	return event->execute(_network, _blockCache, _newEvents, _currentTick);
}

int AsyncEvent::getEventId() const {
	return id;
}
