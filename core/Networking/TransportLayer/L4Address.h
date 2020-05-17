#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_

#include <string>

#include "../NetworkLayer/L3Address.h"

class L4Address {
private:
	L3Address l3Address;
	short port;

public:
	L4Address(short _port);
	L4Address(L3Address _l3address, short _port);
	bool operator==(const L4Address &other) const;
	L3Address getL3Address() const;
	void setL3Address(L3Address l3Address);
	short getPort() const;
	void setPort(short port);
	int getSize();
	long long getHash();
};

template<> struct std::hash<L4Address> {
	std::size_t operator()(L4Address const& l) const noexcept {
		return std::hash<std::string>{}(std::to_string((long long) std::hash<L3Address>{}(l.getL3Address())) + "P" + std::to_string(l.getPort()));
	}
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_ */
