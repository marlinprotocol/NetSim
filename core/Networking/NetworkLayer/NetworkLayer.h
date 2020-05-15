#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>

#include "L3Protocol.h"

class Bandwidth;
class L3Address;
class NetworkMessage;
class Subnet;
class TCPMessage;

class NetworkLayer {
private:
	bool online;
	int partitionGroupId;
	std::shared_ptr<Bandwidth> maxBandwidth;
	std::shared_ptr<Bandwidth> currentBandwidth;
	uint64_t nextFreeSendingTick;
	uint64_t nextFreeReceivingTick;
	std::shared_ptr<Subnet> subnet;

public:
	NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet);
	bool isOnline();
	L3Address getL3Address();
	int getPartitionGroupId() const;
	void setPartitionGroupId(int _partitionGroupId);
	std::shared_ptr<Bandwidth> getCurrentBandwidth();
	std::shared_ptr<Bandwidth> getMaxBandwidth();
	uint64_t getNextFreeReceivingTick() const;
	void setNextFreeReceivingTick(uint64_t _nextFreeReceivingTick);
	uint64_t getNextFreeSendingTick() const;
	void setNextFreeSendingTick(uint64_t _nextFreeSendingTick);
	void send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<TCPMessage> _payload);
	void receive(std::shared_ptr<NetworkMessage> _message);
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
