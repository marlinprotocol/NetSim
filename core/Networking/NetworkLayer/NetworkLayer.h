#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>
#include <vector>

#include "L3Address.h"
#include "L3Protocol.h"
#include "../../Network/Node/NodeId.h"

class Bandwidth;
class Event;
class NetworkMessage;
class Subnet;
class L4Message;
class TransportLayer;

class NetworkLayer {
private:
	bool online;
	int partitionGroupId;
	L3Address myL3Address;
	std::shared_ptr<Bandwidth> maxBandwidth;
	std::shared_ptr<Bandwidth> currentBandwidth;
	uint64_t nextFreeSendingTick;
	uint64_t nextFreeReceivingTick;
	std::shared_ptr<Subnet> subnet;
	std::shared_ptr<TransportLayer> transportLayer;

public:
	NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet, NodeId _myNodeId);
	bool isOnline();
	void setOnline(bool _online);
	L3Address getL3Address();
	int getPartitionGroupId() const;
	void setPartitionGroupId(int _partitionGroupId);
	std::shared_ptr<Bandwidth> getCurrentBandwidth();
	std::shared_ptr<Bandwidth> getMaxBandwidth();
	uint64_t getNextFreeReceivingTick() const;
	std::shared_ptr<TransportLayer> getTransportLayer();
	void setNextFreeReceivingTick(uint64_t _nextFreeReceivingTick);
	uint64_t getNextFreeSendingTick() const;
	void setNextFreeSendingTick(uint64_t _nextFreeSendingTick);
	void send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<L4Message> _payload,
			  uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
	void receive(std::shared_ptr<NetworkMessage> _message);
	std::shared_ptr<Subnet> getSubnet();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
