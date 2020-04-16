#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <memory>

#include "../Blockchain/Cache/BlockCache.h"
#include "../EventManagement/EventManager/EventManager.h"
#include "../Network/Network.h"
#include "../../helpers/Logger/easylogging.h"
#include "../../models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.h"

class Simulator {
private:
	std::shared_ptr<BlockCache> blockCache;
	std::shared_ptr<GlobalOrchestration> globalOrchestration;
	EventManager eventManager;
	Network network;

	void sendGenesisBlockToAllNodes(const Network& network, int genesisBlockId);

public:
	Simulator();
	bool setup();
	void start();
	std::shared_ptr<GlobalOrchestration> getBlockchainManagementModel();
};

#endif /*SIMULATOR_H_*/
