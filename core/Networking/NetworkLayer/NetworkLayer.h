#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>

#include "L3Protocol.h"

class Bandwidth;
class L3Address;
class Subnet;
class TCPMessage;

class NetworkLayer {
private:
	bool online;
	int partitionGroupId;
	std::shared_ptr<Bandwidth> maxBandwidth;
	std::shared_ptr<Bandwidth> currentBandwidth;
	uint64_t nextFreeSendingTime;
	uint64_t nextFreeReceivingTime;
	std::shared_ptr<Subnet> subnet;

public:
	NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet);
	L3Address getL3Address();
	int getPartitionGroupId() const;
	void setPartitionGroupId(int _partitionGroupId);
	std::shared_ptr<Bandwidth> getCurrentBandwidth();
	std::shared_ptr<Bandwidth> getMaxBandwidth();
	uint64_t getNextFreeReceivingTime() const;
	void setNextFreeReceivingTime(uint64_t _nextFreeReceivingTime);
	uint64_t getNextFreeSendingTime() const;
	void setNextFreeSendingTime(uint64_t _nextFreeSendingTime);
	void send(L3Address _dest, L3Protocol _l3Protocol, std::shared_ptr<TCPMessage> _payload);
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
