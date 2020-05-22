#include <memory>
#include <vector>

#include "./EventManager.h"
#include "../../../models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.h"

uint64_t EventManager::currentTick = 0;

EventManager::EventManager(Network& _network, std::shared_ptr<BlockCache> _blockCache, std::shared_ptr<Subnet> _subnet)
			 : network(_network), blockCache(_blockCache), subnet(_subnet) {}

void EventManager::resetSubnet(std::shared_ptr<Subnet> _subnet) {
	subnet = _subnet;
}

int EventManager::addEvent(std::shared_ptr<Event> _event) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "EventManager::addEvent]" 
			   << "[CurrentTick: " << currentTick << ", TicksToEvent: "  << _event->getTicksBeforeExecution() << "]";
	return eventQueue.addEvent(AsyncEvent(_event, currentTick + _event->getTicksBeforeExecution()));
}

EventQueue& EventManager::getEventQueue() {
	return eventQueue;
}

bool EventManager::removeEvent(int _id) {
	return eventQueue.removeEvent(AsyncEvent(_id));
}

bool EventManager::hasNextEvent() {
	return !eventQueue.isEmpty();
}

bool EventManager::executeNextEvent(std::shared_ptr<GlobalOrchestration> _globalOrchestration) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "EventManager::executeNextEvent][TICK_LIMIT_EXCEEDED]";

	if(currentTick>10000) {
		LOG(DEBUG) << "[" << std::setw(35) << std::left << "EventManager::executeNextEvent exiting]"
				   << "[Tickstamp: " << currentTick << "]";
		return false;
	}

	if(eventQueue.isEmpty()) {
		LOG(DEBUG) << "[EventQueue empty]";
		return false;
	}

	AsyncEvent asyncEvent = eventQueue.getNextEvent();
	eventQueue.removeNextEvent();

	currentTick = asyncEvent.getTickToExecOn();

	LOG(DEBUG) << "[Tickstamp: " << std::setw(10) << std::right << currentTick << "]";

	if(asyncEvent.getEvent()->getEventType() == EventType::SCHEDULE_NEXT_BLOCK) {
		_globalOrchestration->scheduleNextBlock(this);
	}
	else {
		std::vector<std::shared_ptr<Event>> newEvents;
		asyncEvent.execute(network, blockCache, newEvents, currentTick, subnet);

		for(auto event: newEvents) {
			addEvent(event);
		}
	}

	return true;
}

std::shared_ptr<BlockCache>EventManager::getBlockCachePtr() {
	return blockCache;
}
