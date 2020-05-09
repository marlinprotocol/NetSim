#include <functional>

#include "TCPMessage.h"
#include "TransportLayer.h"
#include "L4Address.h"
#include "L4Message.h"
#include "L4Protocol.h"
#include "UDPMessage.h"
#include "../NetworkLayer/NetworkLayer.h"

TransportLayer::TransportLayer(std::shared_ptr<NetworkLayer> _networkLayer) : networkLayer(_networkLayer), lastMsgId(0) {}

int TransportLayer::send(short _srcPort, L4Address _dest, L4Protocol _l4Protocol, int _msgId, std::shared_ptr<Message> _payload, bool _isReply) {
	std::shared_ptr<L4Message> l4Message;

	switch(_l4Protocol.getL4ProtocolType()) {
	case L4ProtocolType::UDP:
		l4Message = std::make_shared<UDPMessage>(UDPMessage(_msgId, _payload, _isReply, L4Address(_srcPort), _dest));
		break;

	case L4ProtocolType::TCP:
		L4Address srcL4Address(networkLayer->getL3Address(), _srcPort);
		long long connId = std::hash<L4Address>{}(srcL4Address) << 32 + std::hash<L4Address>{}(_dest);
		if(connIdSeqNumMap.find(connId) == connIdSeqNumMap.end()) {
			connIdSeqNumMap[connId] = 0;
		}
		long long seqNum = connIdSeqNumMap[connId];
		l4Message = std::make_shared<TCPMessage>(TCPMessage(_msgId, _payload, _isReply, L4Address(_srcPort), _dest, seqNum));
		connIdSeqNumMap[connId] = ++seqNum;
		break;
	}

	return lastMsgId;
}

//int TransportLayer::sendWithTimeout(short _srcPort, L4Address _dest, L4Protocol _l4Protocol, std::shared_ptr<Message> _payload, long long _timeout) {
//	int msgId = send(_srcPort, _dest, _l4Protocol, -1, _payload, false);
//
//}

void TransportLayer::forwardToApplication(std::shared_ptr<L4Message> _msg) {

}

void TransportLayer::receive(std::shared_ptr<L4Message> _msg) {
	L4Protocol l4Protocol = _msg->getL4Protocol();

	switch(l4Protocol.getL4ProtocolType()) {
	case L4ProtocolType::UDP:
		forwardToApplication(_msg);
		break;

	case L4ProtocolType::TCP:
		L4Address src = _msg->getSrc();
		L4Address dest = _msg->getSrc();
		long long connId = std::hash<L4Address>{}(src) << 32 + std::hash<L4Address>{}(dest);

		if(connIdSeqNumMap.find(connId) == connIdSeqNumMap.end()) {
			connIdSeqNumMap[connId] = 0;
		}

		long long seqNum = connIdSeqNumMap[connId];

		std::shared_ptr<TCPMessage> msg = std::static_pointer_cast<TCPMessage>(_msg->getPayload());

		if(msg->getSeqNum() == seqNum) {
			forwardToApplication(_msg);
			connIdSeqNumMap[connId] = ++seqNum;
			for(auto queuedMsg: queuedMsgsPerConnId[connId]) {
				if(queuedMsg->getSeqNum() == seqNum) {
					forwardToApplication(queuedMsg);
					connIdSeqNumMap[connId] = ++seqNum;
				}
				else {
					break;
				}
			}
		}
		else if(msg->getSeqNum() < seqNum) {
			// old message repeat
		}
		else {
			queuedMsgsPerConnId[connId].insert(msg);
		}

		break;
	}
}
