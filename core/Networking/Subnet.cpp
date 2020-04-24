#include "Subnet.h"

Subnet::Subnet() {}

Subnet& Subnet::getSubnetInstance() {
	static Subnet subnet;
	return subnet;
}

void Subnet::send(std::shared_ptr<NetworkMessage> msg) {

}
