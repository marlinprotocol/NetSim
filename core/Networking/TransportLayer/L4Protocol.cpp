#include "L4Protocol.h"

L4Protocol::L4Protocol(bool _isReliable, bool _isConnectionOriented) : isReliable(_isReliable), isConnectionOriented(_isConnectionOriented) {}

inline bool L4Protocol::isIsConnectionOriented() const {
	return isConnectionOriented;
}

inline void L4Protocol::setIsConnectionOriented(bool isConnectionOriented) {
	this->isConnectionOriented = isConnectionOriented;
}

inline bool L4Protocol::isIsReliable() const {
	return isReliable;
}

inline void L4Protocol::setIsReliable(bool isReliable) {
	this->isReliable = isReliable;
}
