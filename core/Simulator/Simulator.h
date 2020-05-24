#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <memory>

#include "../Blockchain/Cache/BlockCache.h"
#include "../EventManagement/EventManager/EventManager.h"
#include "../Network/Network.h"
#include "../../helpers/Logger/easylogging.h"
#include "../../models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.h"

class Subnet;

class Simulator {
private:
	std::shared_ptr<BlockCache> blockCache;
	std::shared_ptr<GlobalOrchestration> globalOrchestration;
	std::shared_ptr<Subnet> subnet;
	EventManager eventManager;
	Network network;
	bool isScheduleIsolation;

	void sendGenesisBlockToAllNodes(const Network& network, int genesisBlockId);

public:
	Simulator();
	void resetSubnet(std::shared_ptr<Subnet> _subnet);
	Network& getNetwork();
	std::shared_ptr<Subnet> getSubnet();
	bool setup();
	void start();
	void scheduleIsolation(bool _schedule);
	EventManager& getEventManager();
	std::shared_ptr<GlobalOrchestration> getBlockchainManagementModel();
};

#endif /*SIMULATOR_H_*/
