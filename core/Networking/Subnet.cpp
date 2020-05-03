#include "Subnet.h"
#include "BandwidthModels/gnp/GnpNetBandwidthManager.h"
#include "../Network/Network.h"

Subnet::Subnet(Network& _network) : network(_network), bandwidthManager(std::make_shared<GnpNetBandwidthManager>(_network)) {}

//Subnet& Subnet::getSubnetInstance() {
//	static Subnet subnet;
//	return subnet;
//}
//
//void Subnet::initializeNetwork(Network& _network) {
//	network = _network;
//	bandwidthManager = std::make_shared<GnpNetBandwidthManager>(_network);
//}

std::shared_ptr<AbstractGnpNetBandwidthManager> Subnet::getBandwidthManager() {
	return bandwidthManager;
}

void Subnet::send(std::shared_ptr<NetworkMessage> msg) {

}
