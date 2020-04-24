#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>

class Subnet;

class NetworkLayer {
private:
	bool online;
	double uploadBandwidth;
	double downloadBandwidth;
	Subnet& subnet;

public:
	NetworkLayer(double _uploadBandwidth, double _downloadBandwidth);
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
