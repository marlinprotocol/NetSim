#ifndef CORE_NETWORKING_LATENCYMODELS_PINGER_H_
#define CORE_NETWORKING_LATENCYMODELS_PINGER_H_

#include <string>
#include <unordered_map>

#include "LinkMetrics.h"

class PingER {
private:
	std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>> linkMetrics;

public:
	PingER();
	PingER(std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>>& _linkMetrics);
	void setLinkMetrics(std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>>& _linkMetrics);
	LinkMetrics& getLinkMetrics(std::string src, std::string dest);
};

#endif /* CORE_NETWORKING_LATENCYMODELS_PINGER_H_ */
