#include <string>

#include "./MessageToNodeEvent.h"
#include "../../../Network/Messages/NewBlockIdMessage.h"
#include "../../../Network/Messages/NewBlockMinedMessage.h"

MessageToNodeEvent::MessageToNodeEvent(std::shared_ptr<Message> _message, int _forNodeId, int _fromNodeId, long long _durationInTicks)
				   : message(_message), forNodeId(_forNodeId), fromNodeId(_fromNodeId), Event(_durationInTicks, EventType::MESSAGE_TO_NODE) {}

bool MessageToNodeEvent::execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
								 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {
	LOG(DEBUG) << "[" << std::setw(35) << std::left << "MessageToNodeEvent::execute]"
			   << "[From:" << std::setw(8) << std::right << std::to_string(fromNodeId) << "]"
			   << "[To:" << std::setw(8) << std::right << std::to_string(forNodeId) << "]"
			   << "[Type:" << std::setw(15) << std::right << message->getType() << "]";

	auto node = _network.getNodes()[forNodeId];

	switch(message->getMessageType()) {
		case MessageType::NEW_BLOCK_ID:
			node->onNewBlockIdMessage(std::dynamic_pointer_cast<NewBlockIdMessage>(message), _blockCache, _newEvents);
			break;
		case MessageType::NEW_BLOCK_MINED:
			node->onNewBlockMinedMessage(std::dynamic_pointer_cast<NewBlockMinedMessage>(message), _blockCache, _newEvents, _currentTick);
			break;	
		case MessageType::NEW_BLOCK_BODY:
			break;
	}	

	return true;
}
