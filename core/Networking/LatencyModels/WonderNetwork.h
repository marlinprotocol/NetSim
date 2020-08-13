#ifndef CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_
#define CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_

#include <unordered_map>

#include "City.h"
#include "LinkMetrics.h"
#include "../../../lib/jsoncpp/json.h"

const std::string SOURCE_WONDER_NETWORK_DATA = "../data/pingLatency/pingDataByRegion.json";

class WonderNetwork {
private:
	std::vector <City> citiesMap;
	std::vector <std::vector <LinkMetrics> > cityPairLinkMetrics;
	std::unordered_map <std::string, std::vector <int> > regionCities;
	static WonderNetwork *wonderNetworkInstance;
	WonderNetwork();
public:
	static WonderNetwork *getInstance();
	std::vector <City> getCitiesMap();
	City getCityByIndex(int i);
	LinkMetrics getLinkMetricsBetweenCities(int sourceCityIdx, int destinationCityIdx);
	std::vector <int> getCitiesInRegion(std::string region);
};

#endif /* CORE_NETWORKING_LATENCYMODELS_WONDERNETWORK_H_ */
