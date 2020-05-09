#include <functional>
#include <string>

#include "L4Address.h"
#include "../NetworkLayer/L3Address.h"

L4Address::L4Address(short _port) : l3Address(L3Address()), port(_port) {}

L4Address::L4Address(L3Address _l3Address, short _port) : l3Address(_l3Address), port(_port) {}

inline L3Address L4Address::getL3Address() const {
	return l3Address;
}

inline void L4Address::setL3Address(L3Address _l3Address) {
	l3Address = _l3Address;
}

inline short L4Address::getPort() const {
	return port;
}

inline void L4Address::setPort(short _port) {
	port = _port;
}

int L4Address::getSize() {
	return l3Address.getSize() + sizeof(short);
}

template<> struct std::hash<L4Address> {
	std::size_t operator()(L4Address const& l) const noexcept {
		return std::hash<string>{}(std::to_string((long long) hash<L3Address>{}(l)) + "P" + std::to_string(l.getPort()));
	}
};
