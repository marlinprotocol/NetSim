#ifndef TESTS_TRANSPORTLAYERTEST_H_
#define TESTS_TRANSPORTLAYERTEST_H_

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

class TransportLayerTest {
private:
	Simulator simulator;
	Network& network;
	std::shared_ptr<Subnet> subnet;

public:
	class TestMessage : public Message {
	public:
		TestMessage() : Message(MessageType::TEST) {};

		std::string getType() {
			return "TestMessage";
		}
	};

	TransportLayerTest();
	std::shared_ptr<TestLatencyModel> populatePingER();
	void test1Sender1Receiver1Stream();
	int test();
};

#endif /* TESTS_TRANSPORTLAYERTEST_H_ */
