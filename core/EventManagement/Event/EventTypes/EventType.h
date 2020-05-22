#ifndef EVENTTYPE_H_
#define EVENTTYPE_H_

enum class EventType {MESSAGE_TO_NODE, //messaging
					  SCHEDULE_NEXT_BLOCK, // mining
					  SCHEDULE_ISOLATION_START, SCHEDULE_ISOLATION_STOP, //, TOGGLE_ISOLATION
					  TEST
					  }; // isolation

#endif /*EVENTTYPE_H_*/
