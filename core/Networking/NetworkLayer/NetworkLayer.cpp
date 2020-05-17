#include "NetworkLayer.h"
#include "L3Address.h"
#include "NetworkMessage.h"
#include "../Bandwidth.h"
#include "../LatencyModels/GnpLatencyModel.h"
#include "../Subnet.h"
#include "../../EventManagement/Event/EventTypes/MessageToNodeEvent.h"

NetworkLayer::NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet) :
	online(true), partitionGroupId(-1), subnet(_subnet), nextFreeReceivingTick(0), nextFreeSendingTick(0),
	currentBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))),
	maxBandwidth(std::make_shared<Bandwidth>(Bandwidth(_downloadBandwidth, _uploadBandwidth))) {}

bool NetworkLayer::isOnline() {
	return online;
}

L3Address NetworkLayer::getL3Address() {
	return L3Address();
}

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

uint64_t NetworkLayer::getNextFreeReceivingTick() const {
	return nextFreeReceivingTick;
}

void NetworkLayer::setNextFreeReceivingTick(uint64_t _nextFreeReceivingTime) {
	nextFreeReceivingTick = _nextFreeReceivingTime;
}

uint64_t NetworkLayer::getNextFreeSendingTick() const {
	return nextFreeSendingTick;
}

void NetworkLayer::setNextFreeSendingTick(uint64_t _nextFreeSendingTime) {
	nextFreeSendingTick = _nextFreeSendingTime;
}

void NetworkLayer::send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<TCPMessage> _payload) {
	if(online) {

	}
	else {

	}
}

void NetworkLayer::receive(std::shared_ptr<NetworkMessage> _message) {

}
