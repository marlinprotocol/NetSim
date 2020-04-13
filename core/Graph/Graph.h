#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

#include "../../helpers/Logger/easylogging.h"

class Graph {
private:
	Queue<std::vector<int>> blockchain;
	std::shared_ptr<const BlockCache> blockCache;
	bool addBlockAtHeight(int blockId, int blockHeight);
	std::unique_ptr<BlockchainManagementModel> blockchainManagementModel;

public:
	bool isEdge(int i, int j);
	std::vector<int> getNeighbours(int i);
};

#endif /*GRAPH_H_*/
