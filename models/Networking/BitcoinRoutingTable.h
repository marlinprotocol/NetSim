#ifndef BITCOINROUTINGTABLE_H_
#define BITCOINROUTINGTABLE_H_

#include "../../core/Networking/RoutingTable.h"
#include "../../helpers/Logger/easylogging.h"

class BitcoinRoutingTable : public RoutingTable {
public:
	BitcoinRoutingTable(int _nodeOwnerId);
};

#endif /*BITCOINROUTINGTABLE_H_*/
