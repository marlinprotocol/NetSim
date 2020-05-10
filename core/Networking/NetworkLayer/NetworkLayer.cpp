#include "NetworkLayer.h"
#include "../Bandwidth.h"
#include "../Subnet.h"

NetworkLayer::NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet) :
	online(true), partitionGroupId(-1), subnet(_subnet),
	currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))),
	maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))) {}

int NetworkLayer::getPartitionGroupId() const {
	return partitionGroupId;
}

void NetworkLayer::setPartitionGroupId(int _partitionGroupId) {
	partitionGroupId = _partitionGroupId;
}
