#include "IsolationManager.h"
#include "../../EventManagement/Event/Event.h"
#include "../../EventManagement/Event/EventTypes/EventType.h"
#include "../../EventManagement/EventManager/EventManager.h"
#include "Events/PartitionEvent.h"

bool IsolationManager::getIsolationActive() {
	return isIsolationActive;
}

void IsolationManager::setIsolationActive(bool _isIsolationActive) {
	isIsolationActive = _isIsolationActive;
}

std::unordered_map<int, std::set<NodeId>>& IsolationManager::getPartitionGroups() {
	return partitionGroups;
}

bool IsolationManager::updatePartitionGroup(int _groupId, std::set<NodeId>& _nodes) {
	partitionGroups[_groupId] = _nodes;
	return true;
}

bool IsolationManager::updatePartitionGroups(std::set<NodeId>& _partitionGroups) {
	partitionGroups = _partitionGroups;
	return true;
}

void IsolationManager::schedulePartitionStart(EventManager& _eventManager, uint64_t _ticksBeforeExecution) {
	_eventManager.addEvent(std::shared_ptr<Event>(
								new PartitionEvent(
										EventType::SCHEDULE_ISOLATION_START, _ticksBeforeExecution, shared_from_this()
								)
						   ));
}

void IsolationManager::schedulePartitionStop(EventManager& _eventManager, uint64_t _ticksBeforeExecution) {
	_eventManager.addEvent(std::shared_ptr<Event>(
								new PartitionEvent(
										EventType::SCHEDULE_ISOLATION_STOP, _ticksBeforeExecution, shared_from_this()
								)
						  ));
}

void IsolationManager::eraseResetGroup() {
	partitionGroups.erase(-1);
}
