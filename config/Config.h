#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

const int NUM_REGIONS = 6;

std::string REGIONS[NUM_REGIONS] = {"ASIA", "JAPAN", "AUSTRALIA", "NORTH_AMERICA", "SOUTH_AMERICA", "EUROPE"};

const double REGION_DISTRIBUTION_OF_NODES[NUM_REGIONS] = {0.1177, 0.0224, 0.0195, 0.3316, 0.009, 0.4998};

const long long INTER_REGION_LATENCY[NUM_REGIONS][NUM_REGIONS] = {
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1}	
};

const int NUM_NODES = 14;

const int NUM_CLUSTERS = 3;

const int CLUSTER_SIZE = 3;

const std::string CONSENSUS_TYPE = "PoW";

const int NUM_MINERS = 5;

const int BLOCK_TIME = 600;

#endif /*CONFIG_H_*/
