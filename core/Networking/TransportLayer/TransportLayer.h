#ifndef CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_
#define CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_

#include <memory>
#include <set>
#include <unordered_map>

class TCPMessage;

class TransportLayer {
private:
	std::unordered_map<long long, long long> connIdSeqNumMap;
	std::unordered_map<long long, std::set<std::shared_ptr<TCPMessage>>> queuedMsgsPerConnId;

public:

};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_ */
