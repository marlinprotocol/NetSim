#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>

class Subnet;
class L3Address;

class NetworkLayer {
private:
	bool online;
	double uploadBandwidth;
	double downloadBandwidth;
	Subnet& subnet;

public:
	NetworkLayer(double _uploadBandwidth, double _downloadBandwidth);
	L3Address getL3Address();
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
