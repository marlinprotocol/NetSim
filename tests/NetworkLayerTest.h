#ifndef TESTS_NETWORKLAYERTEST_H_
#define TESTS_NETWORKLAYERTEST_H_

#include <limits>
#include <memory>

#include "../core/Network/Network.h"
#include "../core/Network/Messages/Message.h"
#include "../core/Networking/LatencyModels/GnpLatencyModel.h"
#include "../core/Simulator/Simulator.h"

class TestLatencyModel : public GnpLatencyModel {
private:
	uint64_t tcpThroughput;

public:
	TestLatencyModel(Network& _network) : GnpLatencyModel(_network)  {
		tcpThroughput = std::numeric_limits<uint64_t>::max();
	}

	void setTcpThroughput(uint64_t _tcpThroughput) {
		tcpThroughput = _tcpThroughput;
	}

	uint64_t getTCPThroughput(NodeId senderId, NodeId receiverId, bool _useJitter) {
		return tcpThroughput;
	}

	double getUDPErrorProbability(NodeId senderId, NodeId receiverId, std::shared_ptr<IPv4Message> _msg) {
		return 0;
	}

	uint64_t getPropagationDelay(NodeId _sender, NodeId _receiver) {
		return 0;
	}
};

class NetworkLayerTest {
private:
	Simulator simulator;
	Network& network;
	std::shared_ptr<Subnet> subnet;

	void test1Sender1Receiver1Stream();
	void test1Sender1Receiver2Streams();
	void test1Sender2Receivers2Streams();
	void test2Senders1Receiver2Streams();
	void test1Sender1Receiver1StreamLtdTCPThroughput();
	void test1Sender1Receiver2StreamsLtdTCPThroughput();
	void test1Sender2Receivers2StreamsLtdTCPThroughput();
	void test2Senders1Receiver2StreamsLtdTCPThroughput();
	void test1Sender2Receivers2StreamsOffline();
	void test1Sender2Receivers2StreamsCancelTransmission();

public:
	class TestMessage : public Message {
	public:
		TestMessage() : Message(MessageType::TEST) {};

		std::string getType() {
			return "TestMessage";
		}
	};

	NetworkLayerTest();
	std::shared_ptr<TestLatencyModel> populatePingER();
	int test();
};

#endif /* TESTS_NETWORKLAYERTEST_H_ */
