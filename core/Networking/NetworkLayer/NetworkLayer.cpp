#include "NetworkLayer.h"
#include "../Bandwidth.h"
#include "../Subnet.h"

NetworkLayer::NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet) :
	online(true), partitionGroupId(-1), subnet(_subnet), nextFreeReceivingTime(0), nextFreeSendingTime(0),
	currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))),
	maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))) {}

int NetworkLayer::getPartitionGroupId() const {
	return partitionGroupId;
}

void NetworkLayer::setPartitionGroupId(int _partitionGroupId) {
	partitionGroupId = _partitionGroupId;
}

std::shared_ptr<Bandwidth> NetworkLayer::getCurrentBandwidth() {
	return currentBandwidth;
}

std::shared_ptr<Bandwidth> NetworkLayer::getMaxBandwidth() {
	return maxBandwidth;
}

uint64_t NetworkLayer::getNextFreeReceivingTime() const {
	return nextFreeReceivingTime;
}

void NetworkLayer::setNextFreeReceivingTime(uint64_t nextFreeReceivingTime) {
	this->nextFreeReceivingTime = nextFreeReceivingTime;
}

uint64_t NetworkLayer::getNextFreeSendingTime() const {
	return nextFreeSendingTime;
}

void NetworkLayer::setNextFreeSendingTime(uint64_t nextFreeSendingTime) {
	this->nextFreeSendingTime = nextFreeSendingTime;
}

void NetworkLayer::send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<TCPMessage> _payload) {
	if(online) {

	}
	else {

	}
}
