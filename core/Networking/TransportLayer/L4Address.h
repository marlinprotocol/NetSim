#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_

class L3Address;

class L4Address {
private:
	L3Address l3Address;
	short port;

public:
	L4Address(short _port);
	L4Address(L3Address _l3address, short _port);
	L3Address getL3Address() const;
	void setL3Address(L3Address l3Address);
	short getPort() const;
	void setPort(short port);
	int getSize();
	long long getHash();
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4ADDRESS_H_ */
