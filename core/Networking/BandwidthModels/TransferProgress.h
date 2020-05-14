#ifndef CORE_NETWORKING_BANDWIDTHMODELS_TRANSFERPROGRESS_H_
#define CORE_NETWORKING_BANDWIDTHMODELS_TRANSFERPROGRESS_H_

#include <memory>

class NetworkMessage;

class TransferProgress {
private:
	std::shared_ptr<NetworkMessage> message;
	long long remainingBytes;
	double bandwidth;
	uint64_t transferStartTime;
	bool firstSchedule;
	bool obsolete;

public:
	TransferProgress(std::shared_ptr<NetworkMessage> _message, long long _remainingBytes, double _bandwidth, uint64_t _transferStartTime);
	std::shared_ptr<NetworkMessage> getMessage();
	long long getRemainingBytes(uint64_t _currentTime);
};

#endif /* CORE_NETWORKING_BANDWIDTHMODELS_TRANSFERPROGRESS_H_ */
