#include "Bandwidth.h"

Bandwidth::Bandwidth(double _downBW, double _upBW): downBW(_downBW), upBW(_upBW) {}

double Bandwidth::getDownBW() {
	return downBW;
}

double Bandwidth::getUpBW() {
	return upBW;
}
