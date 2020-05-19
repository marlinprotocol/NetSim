#ifndef TESTS_GNPLATENCYMODELTEST_H_
#define TESTS_GNPLATENCYMODELTEST_H_

#include <memory>

#include "../core/Network/Network.h"
#include "../core/Networking/LatencyModels/GnpLatencyModel.h"
#include "../core/Networking/NetworkLayer/IPv4Message.h"
#include "../core/Networking/TransportLayer/L4Message.h"

class GnpLatencyModelTest {
private:
	std::shared_ptr<Network> network;

public:
	GnpLatencyModelTest();
	std::shared_ptr<GnpLatencyModel> populatePingER();
	void testPingErPropagationDelayGnp(std::shared_ptr<GnpLatencyModel> _pingER);
	void testTransmissionDelay(std::shared_ptr<GnpLatencyModel> _pingER);
	void testErrorProbability(std::shared_ptr<GnpLatencyModel> _pingER);
	void testTcpTroughput(std::shared_ptr<GnpLatencyModel> _pingER);
	int test();

	class IPv4TestMessage : public IPv4Message {
	private:
		int numFragments;

	public:
		IPv4TestMessage(int _numFragments) : IPv4Message() {
			numFragments = _numFragments;
		}

		int getNumFragments() {
			return numFragments;
		}
	};
};

#endif /* TESTS_GNPLATENCYMODELTEST_H_ */
