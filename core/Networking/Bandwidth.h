#ifndef CORE_NETWORKING_BANDWIDTH_H_
#define CORE_NETWORKING_BANDWIDTH_H_

class Bandwidth {
private:
	double downBW;
	double upBW;

public:
	Bandwidth(double downBW, double upBW);
	void resetBandwidth(double downBW, double upBW);
	double getDownBW();
	double getUpBW();
};

#endif /* CORE_NETWORKING_BANDWIDTH_H_ */
