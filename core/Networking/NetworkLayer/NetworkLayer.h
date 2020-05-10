#ifndef CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_
#define CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_

#include <memory>

class Bandwidth;
class Subnet;
class L3Address;

class NetworkLayer {
private:
	bool online;
	int partitionGroupId;
	std::shared_ptr<Bandwidth> maxBandwidth;
	std::shared_ptr<Bandwidth> currentBandwidth;
	std::shared_ptr<Subnet> subnet;

public:
	NetworkLayer(double _downloadBandwidth, double _uploadBandwidth, std::shared_ptr<Subnet> _subnet);
	L3Address getL3Address();
	int getPartitionGroupId() const;
	void setPartitionGroupId(int _partitionGroupId);
};

#endif /* CORE_NETWORKING_NETWORKLAYER_NETWORKLAYER_H_ */
