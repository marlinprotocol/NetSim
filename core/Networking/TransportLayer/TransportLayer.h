#ifndef CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_
#define CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_

#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "TCPMessage.h"

class Event;
class L4Address;
class L4Message;
class L4Protocol;
class Message;
class NetworkLayer;
//class TCPMessage;

struct MessageComparator {
    bool operator()(const std::shared_ptr<TCPMessage>& lhs, const std::shared_ptr<TCPMessage>& rhs) const {
        return lhs->getSeqNum() < rhs->getSeqNum();
    }
};

class TransportLayer {
private:
	std::unordered_map<long long, long long> connIdSeqNumMap;
	std::unordered_map<long long, std::set<std::shared_ptr<TCPMessage>, MessageComparator>> queuedMsgsPerConnId;
	std::shared_ptr<NetworkLayer> networkLayer;

public:
	TransportLayer();
//	TransportLayer(std::shared_ptr<NetworkLayer> _networkLayer);
	void setNetworkLayer(std::shared_ptr<NetworkLayer> _networkLayer);
	void send(short _srcPort, L4Address _dest, std::shared_ptr<L4Protocol> _l4Protocol, int _msgId,
			  std::shared_ptr<Message> _payload, bool _isReply, uint64_t _currentTick, std::vector<std::shared_ptr<Event>>& _newEvents);
//	int sendWithTimeout(short _srcPort, L4Address _dest, L4Protocol _l4Protocol, std::shared_ptr<Message> _payload, long long _timeout);
	void forwardToApplication(std::shared_ptr<L4Message> _msg);
	void receive(std::shared_ptr<L4Message> _msg);
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_TRANSPORTLAYER_H_ */
