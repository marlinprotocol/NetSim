#ifndef CORE_NETWORKING_LATENCYMODELS_CITY_H_
#define CORE_NETWORKING_LATENCYMODELS_CITY_H_

#include <string>

class City {
private:
	int code;
	std::string name;
	std::string country; // not yet set.
	std::string region;

public:
	City();
	City(int _code, std::string _name, std::string _country);
	City(int _code, std::string _name);
	void setCountry(std::string _country);
	void setRegion(std::string _region);
	std::string getName();
	std::string getCountry();
	std::string getRegion();
};

#endif /* CORE_NETWORKING_LATENCYMODELS_CITY_H_ */
