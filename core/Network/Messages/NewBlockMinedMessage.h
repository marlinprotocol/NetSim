#ifndef NEWBLOCKMINEDMESSAGE_H_
#define NEWBLOCKMINEDMESSAGE_H_

#include <memory>

#include "./Message.h"
#include "../../Blockchain/Cache/BlockCache.h"

class NewBlockMinedMessage : public Message {
private:
	double difficulty;

public:
	NewBlockMinedMessage(double _difficulty);
	std::string getType();
};

#endif /*NEWBLOCKMINEDMESSAGE_H_*/
