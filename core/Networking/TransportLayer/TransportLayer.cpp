#include <functional>
#include <iostream>

#include "TCPMessage.h"
#include "TransportLayer.h"
#include "L4Address.h"
#include "L4Message.h"
#include "L4Protocol.h"
#include "UDPMessage.h"
#include "../NetworkLayer/NetworkLayer.h"
#include "../../Network/Messages/Message.h"

TransportLayer::TransportLayer() : networkLayer(nullptr) {}

void TransportLayer::setNetworkLayer(std::shared_ptr<NetworkLayer> _networkLayer) {
	networkLayer = _networkLayer;
}

void TransportLayer::send(short _srcPort, L4Address _dest, std::shared_ptr<L4Protocol> _l4Protocol, int _msgId,
						 std::shared_ptr<Message> _payload, bool _isReply, uint64_t _currentTick,
						 std::vector<std::shared_ptr<Event>>& _newEvents) {
	std::cout<<"TransportLayer::send()"<<std::endl;
	std::shared_ptr<L4Message> l4Message;
	L4Address myL4Address(networkLayer->getL3Address().nodeId, _srcPort);

	switch(_l4Protocol->getL4ProtocolType()) {
	case L4ProtocolType::UDP:
		std::cout<<"L4ProtocolType::UDP"<<std::endl;
		l4Message = std::make_shared<UDPMessage>(UDPMessage(_payload, _isReply, myL4Address, _dest, _msgId));
		break;

	case L4ProtocolType::TCP:
		std::cout<<"L4ProtocolType::TCP"<<std::endl;
		L4Address srcL4Address(networkLayer->getL3Address(), _srcPort);
		long long connId = (std::hash<L4Address>{}(srcL4Address) << 32) + std::hash<L4Address>{}(_dest);
		if(connIdSeqNumMap.find(connId) == connIdSeqNumMap.end()) {
			connIdSeqNumMap[connId] = 0;
		}
		long long seqNum = connIdSeqNumMap[connId];
		l4Message = std::make_shared<TCPMessage>(TCPMessage(_payload, _isReply, myL4Address, _dest, seqNum, _msgId));
		connIdSeqNumMap[connId] = ++seqNum;
		break;
	}

	networkLayer->send(_dest.getL3Address(), L3Protocol::IPv4, l4Message, _currentTick, _newEvents);
}

void TransportLayer::forwardToApplication(std::shared_ptr<L4Message> _msg) {
	std::cout<<"TransportLayer::forwardToApplication()"<<std::endl;
	std::cout<<"sender: "<<_msg->getSrc().getL3Address().nodeId<<":"
			 <<_msg->getSrc().getPort()<<std::endl;
	std::cout<<"type: "<<_msg->getPayload()->getType()<<std::endl;
}

void TransportLayer::receive(std::shared_ptr<L4Message> _msg) {
	std::shared_ptr<L4Protocol> l4Protocol = _msg->getL4Protocol();

	switch(l4Protocol->getL4ProtocolType()) {
	case L4ProtocolType::UDP:
		forwardToApplication(_msg);
		break;

	case L4ProtocolType::TCP:
		L4Address src = _msg->getSrc();
		L4Address dest = _msg->getSrc();
		long long connId = (std::hash<L4Address>{}(src) << 32) + std::hash<L4Address>{}(dest);

		if(connIdSeqNumMap.find(connId) == connIdSeqNumMap.end()) {
			connIdSeqNumMap[connId] = 0;
		}

		long long seqNum = connIdSeqNumMap[connId];

		std::shared_ptr<TCPMessage> msg = std::static_pointer_cast<TCPMessage>(_msg);

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
