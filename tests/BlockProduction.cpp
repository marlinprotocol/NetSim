#include <cstdio>
#include <map>

#include "../core/Simulator/Simulator.h"
#include "../helpers/Logger/easylogging.h"

using namespace std;

INITIALIZE_EASYLOGGINGPP

void configureLogger() {
	// Load configuration from file
    el::Configurations conf1("./config/Logger-conf1.conf");
    el::Configurations networkTopologyConf("./config/Logger-networkTopology.conf");
    // Reconfigure default logger
    el::Loggers::reconfigureLogger("default", conf1);
    // Register another logger apart from default
    el::Logger* networkTopologyLogger = el::Loggers::getLogger("networkTopology");
    // Reconfigure networkTopology logger
    el::Loggers::reconfigureLogger("networkTopology", networkTopologyConf);
}

bool checkBlockTimeMean(Simulator &simulator) {
	//    simulator.start();
	long long sum = 0;
	for (long long i = 0; i < 1000000; i++) {
		int x = simulator.getBlockchainManagementModel()->getNextBlockTime();
//		    	cout<<x<<endl;
		sum += x;
	}

	double avg = sum / 1000000;
	cout << "Avg: " << avg << endl;

	return (avg > 600 - 10) && (avg < 600 + 10);
}

bool checkBlockProducerDistribution(Simulator &simulator) {
	unordered_map<int, int> m;

	for (long long i = 0; i < 100000; i++) {
		int x = simulator.getBlockchainManagementModel()->getNextBlockProducerId();
		if(m.find(x) == m.end()) {
			m.insert(make_pair(x, 1));
		}
		else m[x]++;
	}

	for(auto it: m) {
		cout<<it.first<<" "<<it.second<<endl;
	}

	return true;
}

int main() {
	configureLogger();

	LOG(INFO) << "[Test started]";

	Simulator simulator;
    simulator.setup();
//    simulator.start();

//	checkBlockTimeMean(simulator);

	checkBlockProducerDistribution(simulator);

    LOG(INFO) << "[Test stopped]";

    // Flush all loggers otherwise sometimes program closes and not every log gets printed
    el::Loggers::flushAll();

	return 0;
}
