#ifndef CORE_NETWORKING_SUBNET_H_
#define CORE_NETWORKING_SUBNET_H_

#include <memory>

class NetworkMessage;

class Subnet {
private:
	Subnet();

public:
	static Subnet& getSubnetInstance();
	// Latency Model
	void send(std::shared_ptr<NetworkMessage> msg);
};

#endif /* CORE_NETWORKING_SUBNET_H_ */
