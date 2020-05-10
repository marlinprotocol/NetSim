#include "./Event.h"

Event::Event(uint64_t _ticksBeforeExecution, EventType _eventType) : ticksBeforeExecution(_ticksBeforeExecution), eventType(_eventType) {}

uint64_t Event::getTicksBeforeExecution() {
	return ticksBeforeExecution;
} 

EventType Event::getEventType() {
	return eventType;
}
