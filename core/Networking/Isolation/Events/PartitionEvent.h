#ifndef CORE_NETWORKING_ISOLATION_EVENTS_PARTITIONEVENT_H_
#define CORE_NETWORKING_ISOLATION_EVENTS_PARTITIONEVENT_H_

#include <memory>

#include "../../../EventManagement/Event/Event.h"
#include "../../../EventManagement/Event/EventTypes/EventType.h"

class IsolationManager;

class PartitionEvent : public Event {
private:
	std::shared_ptr<IsolationManager> isolationManager;
//	int groupId;

public:
	PartitionEvent(EventType _eventType, uint64_t _ticksBeforeExecution, std::shared_ptr<IsolationManager> _isolationManager);
	bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
				 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {return true;}
	bool execute(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick);
//	void PartitionEvent::toggleIsolationForGroupId(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents);
	void PartitionEvent::turnIsolationOnForAll(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, bool _on);
};

#endif /* CORE_NETWORKING_ISOLATION_EVENTS_PARTITIONEVENT_H_ */
