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

	for(auto arg: root.getMemberNames()) {
		if(arg == "cityToIdMap") {
			Json::Value cityToIdMap = root["cityToIdMap"];
			for(auto cityName: cityToIdMap.getMemberNames()) {
				// std::cout << it << " " << cityToIdMap[it] << std::endl;
				std::string cityCode = cityToIdMap[cityName].asString();
				std::cout << cityName << " " << cityCode << std::endl;
				citiesMap[cityName] = City(cityCode, cityName);
			}
		} else {
			std::string countryName = arg;
			std::string assignedContinent = regionMap[countryName];

			Json::Value countryData = root[countryName];
			for(auto cityIdx: countryData.getMemberNames()) {
				Json::Value sourceCity = countryData[cityIdx];
				std::string sourceCityName = sourceCity["name"].asString();
				Json::Value sourceCityData = sourceCity["data"];
				// std::cout << sourceCityName << std::endl;

				City cityObject = citiesMap[sourceCityName];
				cityObject.setRegion(assignedContinent);

				for(auto otherCityIdx: sourceCityData.getMemberNames()) {
					Json::Value metricsData = sourceCityData[otherCityIdx];

					std::cout << otherCityIdx << ' ' << metricsData["min"] << ' ' << metricsData["avg"] << ' ' << metricsData["max"] << std::endl;
					if(!metricsData["min"] or !metricsData["max"] or !metricsData["avg"]) {
						continue;
					}
					double minRTT = std::stod(metricsData["min"].asString()), 
						avgRTT = std::stod(metricsData["avg"].asString()),
						maxRTT = std::stod(metricsData["max"].asString());
					LinkMetrics linkMetrics = LinkMetrics(minRTT, avgRTT, maxRTT, 0);

					std::string destinationCityName = metricsData["destination_name"].asString();
					cityPairLinkMetrics[sourceCityName][destinationCityName] = linkMetrics;
					// std::cout << metricsData << std::endl;
				}
			}
			
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