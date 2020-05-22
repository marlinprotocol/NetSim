#include "TransferProgress.h"

#include <iostream>

TransferProgress::TransferProgress(std::shared_ptr<NetworkMessage> _message, long long _remainingBytes, double _bandwidth, uint64_t _transferStartTime) :
		message(_message), remainingBytes(_remainingBytes), bandwidth(_bandwidth), transferStartTime(_transferStartTime), firstSchedule(true), obsolete(false) {
//	std::cout<<"********************"<<std::endl;
//	std::cout<<"transferStartTime: "<<_transferStartTime<<std::endl;
//	std::cout<<"bandwidth: "<<_bandwidth<<std::endl;
//	std::cout<<"remainingBytes: "<<_remainingBytes<<std::endl;
//	std::cout<<"********************"<<std::endl;
}

std::shared_ptr<NetworkMessage> TransferProgress::getMessage() {
	return message;
}

long long TransferProgress::getRemainingBytes(uint64_t _currentTime) {
	if(remainingBytes == 0) return 0;

	long long elapsedTime = _currentTime - transferStartTime;

//	std::cout<<"==================="<<std::endl;
//	std::cout<<"_currentTime: "<<_currentTime<<std::endl;
//	std::cout<<"transferStartTime: "<<transferStartTime<<std::endl;
//	std::cout<<"elapsedTime: "<<elapsedTime<<std::endl;
//	std::cout<<"remainingBytes: "<<remainingBytes<<std::endl;
//	std::cout<<"remainingBytes - (elapsedTime * bandwidth): "<<remainingBytes - (elapsedTime * bandwidth)<<std::endl;
//	std::cout<<"==================="<<std::endl;

	return remainingBytes - (elapsedTime * bandwidth);
}

bool TransferProgress::isFirstSchedule() {
	return firstSchedule;
}

void TransferProgress::setFirstSchedule(bool _firstSchedule) {
	firstSchedule = _firstSchedule;
}

bool TransferProgress::isObsolete() {
	return obsolete;
}

void TransferProgress::setObsolete(bool _obsolete) {
	obsolete = _obsolete;
}
