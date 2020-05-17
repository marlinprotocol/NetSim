#include "TransferProgress.h"

TransferProgress::TransferProgress(std::shared_ptr<NetworkMessage> _message, long long _remainingBytes, double _bandwidth, uint64_t _transferStartTime) :
		message(_message), remainingBytes(_remainingBytes), bandwidth(_bandwidth), transferStartTime(_transferStartTime), firstSchedule(true), obsolete(false) {}

std::shared_ptr<NetworkMessage> TransferProgress::getMessage() {
	return message;
}

long long TransferProgress::getRemainingBytes(uint64_t _currentTime) {
	if(remainingBytes == 0) return 0;

	long long elapsedTime = _currentTime - transferStartTime;
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
