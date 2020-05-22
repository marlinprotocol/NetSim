#ifndef CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_
#define CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_

#include <functional>

#include "../../Network/Node/NodeId.h"

class L3Address {
public:
	L3Address(NodeId _nodeId);
	NodeId nodeId; // TODO: to be eliminated eventually, replaced usage by subclass IPv4Address
	bool operator==(const L3Address &other) const;
	int getSize();
};

//namespace std
//{
    template<> struct std::hash<L3Address>
    {
    	std::size_t operator()(L3Address const& l) const noexcept
        {
            return std::hash<NodeId>{}(l.nodeId); // TODO: recheck
        }
    };
//}

#endif /* CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_ */
