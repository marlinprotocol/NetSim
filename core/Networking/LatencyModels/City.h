#ifndef CORE_NETWORKING_LATENCYMODELS_CITY_H_
#define CORE_NETWORKING_LATENCYMODELS_CITY_H_

#include <string>

class City {
private:
	std::string code;
	std::string name;
	std::string country;

public:
	City();
	City(std::string _code, std::string _name, std::string _country);
	void setCountry(std::string _country);
	std::string getName();
	std::string getCountry();
};

#endif /* CORE_NETWORKING_LATENCYMODELS_CITY_H_ */
