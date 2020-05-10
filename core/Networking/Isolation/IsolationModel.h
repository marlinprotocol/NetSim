#ifndef CORE_NETWORKING_ISOLATION_ISOLATIONMODEL_H_
#define CORE_NETWORKING_ISOLATION_ISOLATIONMODEL_H_

class IsolationModel {
public:
	virtual ~IsolationModel() {};
	virtual long long getPartitionedDuration(int groupId) = 0;
	virtual long long getConnectedDuration(int groupId) = 0;
};

#endif /* CORE_NETWORKING_ISOLATION_ISOLATIONMODEL_H_ */
