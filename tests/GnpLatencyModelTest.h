#ifndef TESTS_GNPLATENCYMODELTEST_H_
#define TESTS_GNPLATENCYMODELTEST_H_

#include <memory>

#include "../core/Network/Network.h"
#include "../core/Networking/LatencyModels/GnpLatencyModel.h"

class GnpLatencyModelTest {
private:
	std::shared_ptr<Network> network;

public:
	GnpLatencyModelTest();
	std::shared_ptr<GnpLatencyModel> populatePingER();
	void testPingErPropagationDelayGnp(std::shared_ptr<GnpLatencyModel> _pingER);
	int test();
};

#endif /* TESTS_GNPLATENCYMODELTEST_H_ */
