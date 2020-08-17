#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <memory>
#include <vector>

#include "../../helpers/Logger/easylogging.h"

#include "../../core/Blockchain/Blockchain.h"
#include "../../core/EventManagement/Event/Event.h"
#include "../../core/Network/Messages/Message.h"
#include "../../core/Network/Messages/NewBlockIdMessage.h"
#include "../../core/Network/Messages/NewBlockMinedMessage.h"
#include "../../core/Networking/RoutingTable.h"


class Protocol {
protected:
	double lambda;
public:
	Protocol();
	virtual ~Protocol() {}
	virtual double getLambda();
	void onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
							 std::vector<std::shared_ptr<Event>>& _newEvents);
	void onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message,
								std::shared_ptr<BlockCache> _blockCache,
								std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick);

};

#endif /*PROTOCOL_H_*/
