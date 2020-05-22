#include <memory>

#include "./Simulator.h"
#include "../Blockchain/Block/Block.h"
#include "../Blockchain/Block/PoWBlock.h"
#include "../Blockchain/Block/PoSBlock.h"
#include "../EventManagement/Event/EventTypes/MessageToNodeEvent.h"
#include "../Network/Messages/Message.h"
#include "../Network/Messages/NewBlockIdMessage.h"
#include "../Networking/Subnet.h"
#include "../Networking/Isolation/IsolationManager.h"
#include "../../config/Config.h"
#include "../../models/BlockchainManagement/GlobalOrchestration/Bitcoin.h"
#include "../../models/NodePlacement/RandomNodeLocations.h"

Simulator::Simulator() : blockCache(std::make_shared<BlockCache>()), subnet(new Subnet(network)),
						 eventManager(network, blockCache, subnet) {
	globalOrchestration = std::shared_ptr<GlobalOrchestration>(new BitcoinModel(network));
	isScheduleIsolation = false;
}

void Simulator::resetSubnet(std::shared_ptr<Subnet> _subnet) {
	subnet = _subnet;
	eventManager.resetSubnet(_subnet);
}

Network& Simulator::getNetwork() {
	return network;
}

bool Simulator::setup() {
	network = getRandomNetwork(blockCache, globalOrchestration, subnet);

	globalOrchestration->scheduleBlockProduction(network, blockCache, eventManager);

	if(isScheduleIsolation) {
		IsolationManager isolationManager;
		isolationManager.schedulePartitionStart(eventManager, 1000);
	}

	return true;
}

void Simulator::start() {
	LOG(INFO) << "[Simulator started]"; 

	while(eventManager.hasNextEvent()) {
		bool toContinue = eventManager.executeNextEvent(globalOrchestration);
		if(!toContinue) break;
	}

	LOG(INFO) << "[Simulator stopped]"; 
}

void Simulator::scheduleIsolation(bool _schedule) {
	isScheduleIsolation = _schedule;
}

EventManager& Simulator::getEventManager() {
	return eventManager;
}

std::shared_ptr<GlobalOrchestration> Simulator::getBlockchainManagementModel() {
	return globalOrchestration;
}
