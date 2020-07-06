#ifndef FLEXIBLEROUTINGTABLE_H_
#define FLEXIBLEROUTINGTABLE_H_

#include "../../core/Networking/RoutingTable.h"
#include "../../helpers/Logger/easylogging.h"

class FlexibleRoutingTable : public RoutingTable {
public:
	FlexibleRoutingTable(int _nodeOwnerId);
};

#endif /*FLEXIBLEROUTINGTABLE_H_*/
