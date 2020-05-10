#ifndef CORE_NETWORKING_ISOLATION_ISOLATIONMANAGER_H_
#define CORE_NETWORKING_ISOLATION_ISOLATIONMANAGER_H_

#include <memory>
#include <set>
#include <unordered_map>

#include "../../Network/Node/NodeId.h"

class EventManager;

class IsolationManager : std::enable_shared_from_this<IsolationManager> {
private:
	bool isIsolationActive = false;
	std::unordered_map<int, std::set<NodeId>> partitionGroups;

public:
	bool getIsolationActive();
	void setIsolationActive(bool _isIsolationActive);
	std::unordered_map<int, std::set<NodeId>>& getPartitionGroups();
	bool updatePartitionGroup(int _groupId, std::set<NodeId>& _nodes);
	bool updatePartitionGroups(std::set<NodeId>& _partitionGroups);
	void schedulePartitionStart(EventManager& _eventManager, uint64_t _ticksBeforeExecution);
	void schedulePartitionStop(EventManager& _eventManager, uint64_t _ticksBeforeExecution);
	void eraseResetGroup();
};

#endif /* CORE_NETWORKING_ISOLATION_ISOLATIONMANAGER_H_ */
