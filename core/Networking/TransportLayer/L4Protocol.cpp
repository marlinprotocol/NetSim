#include "L4Protocol.h"

L4Protocol::L4Protocol(L4ProtocolType _l4ProtocolType, bool _isReliable, bool _isConnectionOriented) :
		l4ProtocolType(_l4ProtocolType), isReliable(_isReliable), isConnectionOriented(_isConnectionOriented) {}

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

inline L4ProtocolType L4Protocol::getL4ProtocolType() {
	return l4ProtocolType;
}
