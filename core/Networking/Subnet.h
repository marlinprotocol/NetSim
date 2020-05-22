#ifndef CORE_NETWORKING_SUBNET_H_
#define CORE_NETWORKING_SUBNET_H_

#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "../Network/Node/NodeId.h"

class AbstractGnpNetBandwidthManager;
class Event;
class GnpNetBandwidthAllocation;
class GnpLatencyModel;
class Message;
class Network;
class NetworkMessage;
class Node;
class SubnetMessage;
class TransferProgress;

class Subnet {
private:
	Network& network;
	uint64_t lastMsgId;
	uint64_t nextRescheduleTime;
	std::shared_ptr<AbstractGnpNetBandwidthManager> bandwidthManager;
	std::shared_ptr<GnpLatencyModel> latencyModel;
	std::unordered_map<std::shared_ptr<GnpNetBandwidthAllocation>,
					   std::set<std::shared_ptr<TransferProgress>>> connectionsToTransfersMap;
	std::unordered_map<int, std::shared_ptr<TransferProgress>> messageIdsToTransfersMap;
	std::set<std::shared_ptr<TransferProgress>> cancelledTransfers;

	bool shouldDropMsg(NodeId senderId, NodeId receiverId, std::shared_ptr<NetworkMessage> msg);
	uint64_t setMessageId(std::shared_ptr<NetworkMessage> msg);

public:
	Subnet(Network& _network);
	Subnet(Network& _network, std::shared_ptr<GnpLatencyModel> _latencyModel);
//	static Subnet& getSubnetInstance();
//	void initializeNetwork(Network& _network);
	std::shared_ptr<AbstractGnpNetBandwidthManager> getBandwidthManager();
	std::shared_ptr<GnpLatencyModel> getLatencyModel();
	void send(std::shared_ptr<NetworkMessage> msg, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void cancelTransmission(int _msgId, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void onDisconnect(NodeId _nodeId, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void forwardToReceiverNetworkLayer(std::shared_ptr<NetworkMessage> msg, std::shared_ptr<Node> sender, std::shared_ptr<Node> receiver);
	void addToReceiverQueue(std::shared_ptr<NetworkMessage> _message, std::shared_ptr<Node> _sender, std::shared_ptr<Node> _receiver,
							uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void onMessageReceived(std::shared_ptr<TransferProgress> _tp, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void onBandwidthReallocation(uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void rescheduleTransfers(std::shared_ptr<GnpNetBandwidthAllocation>, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void onSubnetMessage(std::shared_ptr<SubnetMessage> msg, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
};

#endif /* CORE_NETWORKING_SUBNET_H_ */
