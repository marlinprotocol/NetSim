#include "./IPv4Address.h"

#include <sstream>
#include <string>
#include <vector>


IPv4Address::IPv4Address(std::string _id) : id(IPv4StringToLong(_id)) {}

IPv4Address::IPv4Address(long long _id) : id(_id) {}

long long IPv4Address::IPv4StringToLong(std::string _id) {
	long long idLong = 0;

	std::stringstream id(_id);
	std::string segment;
	std::vector<std::string> seglist;

	while(std::getline(id, segment, '.'))
	{
	   seglist.push_back(segment);
	}

	if(seglist.size() == 4) {
		idLong += (stoll(seglist[0])) << 24;
		idLong += (stoll(seglist[1])) << 16;
		idLong += (stoll(seglist[2])) << 8;
		idLong += stoll(seglist[3]);
	}

	return idLong;
}

std::string IPv4Address::IPv4LongToString(unsigned long long _id) {
	std::string idString = "";

	idString  += std::to_string((_id << 32) >> 56) + ".";
	idString  += std::to_string((_id << 40) >> 56) + ".";
	idString  += std::to_string((_id << 48) >> 56) + ".";
	idString  += std::to_string((_id << 56) >> 56);

	return idString;
}

long long IPv4Address::getIPv4AddressLong() {
	return id;
}

std::string IPv4Address::getIPv4AddressString() {
	return IPv4LongToString(id);
}
