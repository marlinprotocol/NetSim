#include "./NewBlockMinedMessage.h"
#include "../../Blockchain/Block/Block.h"
#include "../../Blockchain/Block/PoWBlock.h"

NewBlockMinedMessage::NewBlockMinedMessage(double _difficulty)
	: Message(MessageType::NEW_BLOCK_MINED), difficulty(_difficulty) {}

std::string NewBlockMinedMessage::getType() {
	return "NewBlockMinedMessage";
}
