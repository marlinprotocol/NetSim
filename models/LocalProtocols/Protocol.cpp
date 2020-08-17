#include "Protocol.h"

Protocol::Protocol() {}

double Protocol::getLambda() {
    return lambda;
}

void Protocol::onNewBlockIdMessage(std::shared_ptr<NewBlockIdMessage> _message, std::shared_ptr<BlockCache> _blockCache,
                                std::vector<std::shared_ptr<Event>>& _newEvents) {

}

void Protocol::onNewBlockMinedMessage(std::shared_ptr<NewBlockMinedMessage> _message,
								std::shared_ptr<BlockCache> _blockCache,
								std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick) {
}
