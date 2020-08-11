#include "City.h"

City::City() : code("-1"), name(""), country("") {};

City::City(std::string _code, std::string _name, std::string _country) :
	code(_code), name(_name), country(_country) {};

City::City(std::string _code, std::string _name) :
	code(_code), name(_name) {};



void City::setCountry(std::string _country) {
	country = _country;
}

void City::setRegion(std::string _region) {
	region = _region;
}

std::string City::getName() {
	return name;
}

std::string City::getCountry() {
	return country;
}
