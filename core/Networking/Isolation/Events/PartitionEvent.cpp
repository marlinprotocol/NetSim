#include "PartitionEvent.h"
#include "../IsolationManager.h"
#include "../../NetworkLayer/NetworkLayer.h"

PartitionEvent::PartitionEvent(EventType _eventType, uint64_t _ticksBeforeExecution,
							   std::shared_ptr<IsolationManager> _isolationManager) :
							   isolationManager(_isolationManager), Event(_ticksBeforeExecution, _eventType) {}

//void PartitionEvent::toggleIsolationForGroupId(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents) {
//	if(!isolationManager->getIsolationActive()) {
//		return;
//	}
//
//	auto nodes =  isolationManager->getPartitionGroups()[groupId];
//	if()
//}

void PartitionEvent::turnIsolationOnForAll(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, bool _on) {
	for(auto partition: isolationManager->getPartitionGroups()) {
		for(auto nodeId: partition.second) {
			if(_on) {
				_network.getNode(nodeId)->getNetworkLayer()->setPartitionGroupId(partition.first);
			}
			else {
				_network.getNode(nodeId)->getNetworkLayer()->setPartitionGroupId(-1);
			}
		}
	}
}

bool PartitionEvent::execute(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "PartitionEvent::execute] : " ;
	if(getEventType() == EventType::SCHEDULE_ISOLATION_START) {
//		assert(groupId == -1);
//		isolationManager->setIsolationActive(true);
		turnIsolationOnForAll(_network, _newEvents, true);
		isolationManager->eraseResetGroup();
	}
	else if(getEventType() == EventType::SCHEDULE_ISOLATION_STOP) {
//		groupId = -1;
//		isolationManager->setIsolationActive(false);
		turnIsolationOnForAll(_network, _newEvents, false);
	}
//	else if(eventType == EventType::TOGGLE_ISOLATION) {
//		toggleIsolationForGroupId(_network, _newEvents);
//	}
	return true;
};
