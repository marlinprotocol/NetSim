#include <cmath>

#include "GnpLatencyModel.h"
#include "../NetworkLayer/IPv4Message.h"
#include "../TransportLayer/L4Message.h"
#include "../TransportLayer/TCPMessage.h"
#include "../../Network/Network.h"
#include "../../Network/Node/Node.h"
#include <cassert>

int GnpLatencyModel::MSS;

GnpLatencyModel::GnpLatencyModel(Network& _network) : network(_network) {
	MSS = IPv4Message::MTU_SIZE - IPv4Message::HEADER_SIZE - TCPMessage::HEADER_SIZE;
	wonderNetwork = wonderNetwork->getInstance();
}

//void GnpLatencyModel::setPingER(PingER& _pingER) {
//	pingER = _pingER;
//}

// PingER& GnpLatencyModel::getPingER() {
// 	return pingER;
// }

double GnpLatencyModel::getMinRTT(NodeId senderId, NodeId receiverId) {
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	double rtt = 0;
	rtt = wonderNetwork->getLinkMetricsBetweenCities(sender->getCityIdx(), receiver->getCityIdx()).getMinRTT();

	return rtt;
}

double GnpLatencyModel::getPacketLossProbability(NodeId senderId, NodeId receiverId) {
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	double oneWayLossRate = 0;

	double twoWayLossRate = wonderNetwork->getLinkMetricsBetweenCities(sender->getCityIdx(), receiver->getCityIdx()).getPacketLoss();
	twoWayLossRate /= 100;
	oneWayLossRate = 1 - sqrt(1 - twoWayLossRate);

	return oneWayLossRate;
}

double GnpLatencyModel::getNextJitter(NodeId senderId, NodeId receiverId) {
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	return 0;
}

double GnpLatencyModel::getAvgJitter(NodeId senderId, NodeId receiverId) {
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	double minRTT = wonderNetwork->getLinkMetricsBetweenCities(sender->getCityIdx(), receiver->getCityIdx()).getMinRTT();
	double avgRTT = wonderNetwork->getLinkMetricsBetweenCities(sender->getCityIdx(), receiver->getCityIdx()).getAvgRTT();

	return avgRTT - minRTT;
}

double GnpLatencyModel::getUDPErrorProbability(NodeId senderId, NodeId receiverId, std::shared_ptr<IPv4Message> msg) {
	if(msg->getPayload() != nullptr && msg->getPayload()->getSize() > 65507) {
		// warn("Message-Size is too big for a UDP-Datagramm (max 65507 byte)");
	}

	double lp = getPacketLossProbability(senderId, receiverId);
	double errorProb = 1 - pow(1 - lp, msg->getNumFragments());

	return errorProb;
}

uint64_t GnpLatencyModel::getTransmissionDelay(long long bytes, double bandwidth) {
	if(bandwidth == 0) assert(false);
	return round(bytes/bandwidth);
}

uint64_t GnpLatencyModel::getPropagationDelay(NodeId senderId, NodeId receiverId) {
	std::shared_ptr<Node> sender = network.getNode(senderId);
	std::shared_ptr<Node> receiver = network.getNode(receiverId);

	auto rtt = wonderNetwork->getLinkMetricsBetweenCities(sender->getCityIdx(), receiver->getCityIdx()).getAvgRTT();
	return rtt / 2;
}

uint64_t GnpLatencyModel::getTCPThroughput(NodeId senderId, NodeId receiverId, bool _useJitter) {
	double minRtt = getMinRTT(senderId, receiverId);
	double avgJitter = getAvgJitter(senderId, receiverId);
	if(!_useJitter) avgJitter = 0;
	double packetLossRate = getPacketLossProbability(senderId, receiverId);
	double mathisBW = ((MSS * 1000) / (minRtt + avgJitter)) * sqrt(1.5 / packetLossRate);
	return mathisBW;
}

long long GnpLatencyModel::getLatency(NodeId _sender, NodeId _receiver) {
	return getPropagationDelay(_sender, _receiver);
}
