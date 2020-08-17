#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
// #include "json/value.h"
#include <sstream>

#include "WonderNetwork.h"
#include "../../../lib/jsoncpp/json.h"
#include "../../../helpers/Logger/easylogging.h"
#include "./City.h"
#include "../../../config/Config.h"




WonderNetwork* WonderNetwork::wonderNetworkInstance = 0;


WonderNetwork::WonderNetwork() {
	std::ifstream ifs("../data/pingLatency/pingDataByRegion.json");
	if(!ifs) {
		std::cout << "not opening" << std::endl;
		return;
	}
	Json::Value root;
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;

	if (!Json::parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		return;
	}
	
	std::unordered_map <std::string, std::string> regionMap;
	regionMap["Africa"] = "ASIA";
	regionMap["Asia Pacific"] = "ASIA";
	regionMap["Australia"] = "AUSTRALIA";
	regionMap["China"] = "ASIA";
	regionMap["Eastern Europe"] = "EUROPE";
	regionMap["Japan"] = "ASIA";
	regionMap["MENA"] = "ASIA";
	regionMap["North America"] = "NORTH_AMERICA";
	regionMap["Russia"] = "ASIA";
	regionMap["South America"] = "SOUTH_AMERICA";
	regionMap["South Asia"] = "ASIA";
	regionMap["Western Europe"] = "EUROPE";

	std::unordered_map <std::string, int> regionIdx;
	for(int i = 0; i < NUM_REGIONS; i++) {
		regionIdx[REGIONS[i]] = i;
	}

	Json::Value cityToIdMap = root["cityToIdMap"];

	const int NUMBER_OF_CITIES = 300; // Subject to change.
	citiesMap.resize(NUMBER_OF_CITIES);
	cityPairLinkMetrics.resize(NUMBER_OF_CITIES);
	for(auto &v: cityPairLinkMetrics) {
		v.resize(NUMBER_OF_CITIES);
	}
	std::cout << "[WonderNetwork.cpp]	" << NUMBER_OF_CITIES << ' ' << citiesMap.size() << std::endl;

	for(auto cityName: cityToIdMap.getMemberNames()) {
		int cityCode = std::stoi(cityToIdMap[cityName].asString());
		citiesMap[cityCode] = City(cityCode, cityName);
	}


	for(auto arg: root.getMemberNames()) {
		if(arg == "cityToIdMap") {
			continue;
		}

		std::string countryName = arg;
		std::string assignedRegion = regionMap[countryName];

		Json::Value countryData = root[countryName];
		for(auto sourceCityIdx: countryData.getMemberNames()) {
			Json::Value sourceCity = countryData[sourceCityIdx];
			std::string sourceCityName = sourceCity["name"].asString();
			Json::Value sourceCityData = sourceCity["data"];
			regionCities[assignedRegion].push_back(stoi(sourceCityIdx));
			// std::cout << sourceCityName << std::endl;

			City &cityObject = citiesMap[stoi(sourceCityIdx)];
			std::cout << assignedRegion << std::endl;
			cityObject.setRegion(assignedRegion);

			for(auto destinationCityIdx: sourceCityData.getMemberNames()) {
				Json::Value metricsData = sourceCityData[destinationCityIdx];

				// std::cout << sourceCityIdx << ' ' << destinationCityIdx << ' ' << metricsData["min"] << ' ' << metricsData["avg"] << ' ' << metricsData["max"] << std::endl;
				if(!metricsData["min"] or !metricsData["max"] or !metricsData["avg"]) {
					continue;
				}
				double minRTT = std::stod(metricsData["min"].asString()), 
					avgRTT = std::stod(metricsData["avg"].asString()),
					maxRTT = std::stod(metricsData["max"].asString());
				LinkMetrics linkMetrics = LinkMetrics(minRTT, avgRTT, maxRTT, 0);

				std::string destinationCityName = metricsData["destination_name"].asString();
				cityPairLinkMetrics[stoi(sourceCityIdx)][stoi(destinationCityIdx)] = linkMetrics;
				std::cout << sourceCityIdx << ' ' << destinationCityIdx << std::endl;
				// std::cout << metricsData << std::endl;
			}
		}


	// 	int i=0;
	// 	for(auto it: root) {
	// 		std::cout << it << std::endl;
	// 		if(i==0) {
	// 			for(auto it2: it) {
	// 				std::string cityCode = it2["id"].asString().c_str();
	// 				std::string cityName = it2["name"].asString().c_str();
	// 				citiesMap[cityCode] = City(cityCode, cityName, "");
	// 			}
	// 		}
	// 		else if (i==1) {
	// //			auto it2 = it.begin();
	// 			for(int j = 0; j < it.getMemberNames().size(); j++) {
	// 				std::string srcCityCode = it.getMemberNames()[j];
	// //				std::cout << srcCityCode << " - ";
	// 				auto it2 = it[it.getMemberNames()[j]];
	// 				int k = 0;
	// 				for(; k < (it2).getMemberNames().size() - 1; k++) {
	// 					std::string destCityCode = it2.getMemberNames()[k];
	// 					double avgRTT = std::atof(it2[(it2).getMemberNames()[k]]["avg"].asString().c_str());
	// 					double minRTT = std::atof(it2[(it2).getMemberNames()[k]]["min"].asString().c_str());
	// 					double maxRTT = std::atof(it2[(it2).getMemberNames()[k]]["max"].asString().c_str());
	// 					linkMetrics[srcCityCode][destCityCode] = LinkMetrics(minRTT, avgRTT, maxRTT, 0);
	// //					std::cout << destCityCode << ", ";
	// 				}
	// 				std::string destCityCode = it2.getMemberNames()[k];
	// 				std::string srcCountry = it2[(it2).getMemberNames()[k]]["country"].asString().c_str();
	// 				citiesMap[srcCityCode].setCountry(srcCountry);
	// //				std::cout << destCityCode << " : " << srcCountry;
	// //				std::cout << std::endl;
	// 			}
	// 		}
	// 		i++;
	// 	}
	// 	// std::cout << citiesMap.size() << std::endl;
	// 	for(auto city: citiesMap) {
	// 		std::cout<<std::endl<<city.second.getName()<<" ("<<city.second.getCountry()<<")"<<std::endl;
	// 		std::cout<<"===================="<<std::endl<<std::endl;
	// 		for(auto destination: linkMetrics[city.first]) {
	// 			std::cout << citiesMap[destination.first].getName()
	// 					  << " (" << citiesMap[destination.first].getCountry() << ") - "
	// 					  << "MinRTT: " << linkMetrics[city.first][destination.first].getMinRTT()
	// 					  << "  AvgRTT: " << linkMetrics[city.first][destination.first].getAvgRTT()
	// 					  << "  MaxRTT: " << linkMetrics[city.first][destination.first].getMaxRTT()
	// 					  << std::endl << std::endl;
	// 		}
	// 	}
	}
}


std::vector <City> WonderNetwork::getCitiesMap() {
	return citiesMap;
}

LinkMetrics WonderNetwork::getLinkMetricsBetweenCities(int sourceCityIdx, int destinationCityIdx) {
	return cityPairLinkMetrics[sourceCityIdx][destinationCityIdx];
}

std::vector <int> WonderNetwork::getCitiesInRegion(std::string region) {
	return regionCities[region];
}

City WonderNetwork::getCityByIndex(int i) {
	return citiesMap[i];
}


WonderNetwork* WonderNetwork::getInstance() {
	if(!wonderNetworkInstance) {
		wonderNetworkInstance = new WonderNetwork();
	}
	return wonderNetworkInstance;
	// return new WonderNetwork();
}