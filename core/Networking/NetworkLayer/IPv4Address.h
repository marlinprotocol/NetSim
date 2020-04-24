#ifndef CORE_NETWORKING_NETWORKLAYER_IPV4ADDRESS_H_
#define CORE_NETWORKING_NETWORKLAYER_IPV4ADDRESS_H_

//#include <iostream>
#include <string>

class IPv4Address {
private:
	long long id;

public:
	IPv4Address(std::string _id);
	IPv4Address(long long _id);
	long long IPv4StringToLong(std::string _id);
	std::string IPv4LongToString(unsigned long long _id);
	long long getIPv4AddressLong();
	std::string getIPv4AddressString();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_IPV4ADDRESS_H_ */

//int main() {
//	IPv4Address ip1("255.0.1.44");
//	std::cout<<ip1.getIPv4AddressString()<<std::endl;
//	std::cout<<ip1.getIPv4AddressLong()<<std::endl;
//}
