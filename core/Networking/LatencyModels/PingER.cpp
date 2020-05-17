#include "PingER.h"

PingER::PingER() {}

PingER::PingER(std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>>& _linkMetrics)
	   : linkMetrics(_linkMetrics) {}

void PingER::setLinkMetrics(std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>>& _linkMetrics) {
	linkMetrics = _linkMetrics;
}

LinkMetrics& PingER::getLinkMetrics(std::string src, std::string dest) {
	return linkMetrics[src][dest];
}
