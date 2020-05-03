#ifndef TESTS_SUBNETTEST_H_
#define TESTS_SUBNETTEST_H_

#include <iostream>
#include <memory>

class Network;
class Subnet;

class SubnetTest {
private:
	std::shared_ptr<Subnet> subnet;
	std::shared_ptr<Network> network;

public:
	SubnetTest();
	void AllAtOnce_FullAllocation_OneStream();
	void AllAtOnce_FullAllocation_MultiStream();
	void StepByStep_FullAllocation_OneStream();
	void allAtOnce_RestrictedAllocation_MultiStream();
	int test();
};

#endif /* TESTS_SUBNETTEST_H_ */
