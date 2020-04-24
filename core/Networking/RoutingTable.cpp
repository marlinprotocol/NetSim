#include "RoutingTable.h"

RoutingTable::RoutingTable(int _nodeOwnerId) {
	nodeOwnerId = _nodeOwnerId;
	maxOutConnections = 99999;   // random default
	maxInConnections = 99999;	 // random default
}

bool RoutingTable::setup() {
	
	return true;
}

int RoutingTable::getNumOutConnections() {
	return outConnections.size();
}

int RoutingTable::getNumInConnections() {
	return inConnections.size();
}

bool RoutingTable::setMaxOutConnections(int _maxOutConnections) {
	maxOutConnections = _maxOutConnections;
	return true;
}


int RoutingTable::getMaxOutConnections() {
	return maxOutConnections;
}

bool RoutingTable::setMaxInConnections(int _maxInConnections) {
	maxInConnections = _maxInConnections;
	return true;
}

int RoutingTable::getMaxInConnections() {
	return maxInConnections;
}

bool RoutingTable::addOutConnection(int nodeId) {
	if(outConnections.size() == maxOutConnections || nodeId==nodeOwnerId) {
		return false;
	}

	outConnections.insert(nodeId);
	return true;
}

bool RoutingTable::removeOutConnection(int nodeId) {
	outConnections.erase(nodeId);
	return true;
}

bool RoutingTable::addInConnection(int nodeId) {
	if(inConnections.size() == maxInConnections || nodeId==nodeOwnerId) {
		return false;
	}

	inConnections.insert(nodeId);
	return true;
}

bool RoutingTable::removeInConnection(int nodeId) {
	inConnections.erase(nodeId);
	return true;
}

std::set<int> RoutingTable::getOutConnections() {
	return outConnections;
}

std::set<int> RoutingTable::getInConnections() {
	return inConnections;
}
