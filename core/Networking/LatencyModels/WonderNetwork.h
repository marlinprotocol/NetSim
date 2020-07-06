#ifndef CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_
#define CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_

#include <unordered_map>

#include "City.h"
#include "LinkMetrics.h"
#include "../../../lib/jsoncpp/json.h"

const std::string SOURCE_WONDER_NETWORK_DATA = "./data/pingLatency/data.json";

class WonderNetwork {
private:
	std::unordered_map<std::string, City> citiesMap;
	std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>> linkMetrics;

public:
	WonderNetwork();
};

#endif /* CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_ */
