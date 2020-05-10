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

Simulator::Simulator() : blockCache(std::make_shared<BlockCache>()), eventManager(network, blockCache) {
	globalOrchestration = std::shared_ptr<GlobalOrchestration>(new BitcoinModel(network));
	subnet = std::shared_ptr<Subnet>(new Subnet(network));
}

bool Simulator::setup() {
	network = getRandomNetwork(blockCache, globalOrchestration, subnet);

	globalOrchestration->scheduleBlockProduction(network, blockCache, eventManager);

	IsolationManager isolationManager;
	isolationManager.schedulePartitionStart(eventManager, 1000);

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

std::shared_ptr<GlobalOrchestration> Simulator::getBlockchainManagementModel() {
	return globalOrchestration;
}
