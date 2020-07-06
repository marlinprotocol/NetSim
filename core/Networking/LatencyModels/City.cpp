#include "City.h"

City::City() : code("-1"), name(""), country("") {};

City::City(std::string _code, std::string _name, std::string _country) :
	code(_code), name(_name), country(_country) {};


void City::setCountry(std::string _country) {
	country = _country;
}

std::string City::getName() {
	return name;
}

std::string City::getCountry() {
	return country;
}
