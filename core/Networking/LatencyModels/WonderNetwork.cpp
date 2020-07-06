#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "WonderNetwork.h"
#include "../../../lib/jsoncpp/json.h"

WonderNetwork::WonderNetwork() {
	std::ifstream ifs(SOURCE_WONDER_NETWORK_DATA);

	Json::Value root;

	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;

	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		return;
	}

	int i=0;
	for(auto it: root) {
		if(i==0) {
			for(auto it2: it) {
				std::string cityCode = it2["id"].asString().c_str();
				std::string cityName = it2["name"].asString().c_str();
				citiesMap[cityCode] = City(cityCode, cityName, "");
			}
		}
		else if (i==1) {
//			auto it2 = it.begin();
			for(int j = 0; j < it.getMemberNames().size(); j++) {
				std::string srcCityCode = it.getMemberNames()[j];
//				std::cout << srcCityCode << " - ";
				auto it2 = it[it.getMemberNames()[j]];
				int k = 0;
				for(; k < (it2).getMemberNames().size() - 1; k++) {
					std::string destCityCode = it2.getMemberNames()[k];
					double avgRTT = std::atof(it2[(it2).getMemberNames()[k]]["avg"].asString().c_str());
					double minRTT = std::atof(it2[(it2).getMemberNames()[k]]["min"].asString().c_str());
					double maxRTT = std::atof(it2[(it2).getMemberNames()[k]]["max"].asString().c_str());
					linkMetrics[srcCityCode][destCityCode] = LinkMetrics(minRTT, avgRTT, maxRTT, 0);
//					std::cout << destCityCode << ", ";
				}
				std::string destCityCode = it2.getMemberNames()[k];
				std::string srcCountry = it2[(it2).getMemberNames()[k]]["country"].asString().c_str();
				citiesMap[srcCityCode].setCountry(srcCountry);
//				std::cout << destCityCode << " : " << srcCountry;
//				std::cout << std::endl;
			}
		}
		i++;
	}

	for(auto city: citiesMap) {
		std::cout<<std::endl<<city.second.getName()<<" ("<<city.second.getCountry()<<")"<<std::endl;
		std::cout<<"===================="<<std::endl<<std::endl;
		for(auto destination: linkMetrics[city.first]) {
			std::cout << citiesMap[destination.first].getName()
					  << " (" << citiesMap[destination.first].getCountry() << ") - "
					  << "MinRTT: " << linkMetrics[city.first][destination.first].getMinRTT()
					  << "  AvgRTT: " << linkMetrics[city.first][destination.first].getAvgRTT()
					  << "  MaxRTT: " << linkMetrics[city.first][destination.first].getMaxRTT()
					  << std::endl << std::endl;
		}
	}
}
