#ifndef CORE_NETWORKING_SUBNET_H_
#define CORE_NETWORKING_SUBNET_H_

#include <memory>

class Network;
class NetworkMessage;
class AbstractGnpNetBandwidthManager;

class Subnet {
private:
	Network& network;
	std::shared_ptr<AbstractGnpNetBandwidthManager> bandwidthManager;

public:
	Subnet(Network& _network);
//	static Subnet& getSubnetInstance();
//	void initializeNetwork(Network& _network);
	std::shared_ptr<AbstractGnpNetBandwidthManager> getBandwidthManager();
	void send(std::shared_ptr<NetworkMessage> msg);
};

#endif /* CORE_NETWORKING_SUBNET_H_ */
