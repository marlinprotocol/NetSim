#include "./Event.h"

Event::Event(uint64_t _durationInTicks, EventType _eventType) : durationInTicks(_durationInTicks), eventType(_eventType) {}

uint64_t Event::getDurationInTicks() {
	return durationInTicks;
} 

EventType Event::getEventType() {
	return eventType;
}
