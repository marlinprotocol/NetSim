#include "NetworkLayer.h"
#include "../Subnet.h"

NetworkLayer::NetworkLayer(double _uploadBandwidth, double _downloadBandwidth) :
	online(true), uploadBandwidth(_uploadBandwidth), downloadBandwidth(_downloadBandwidth), subnet(Subnet::getSubnetInstance()) {}
