#ifndef HELPERS_RANDOM_H_
#define HELPERS_RANDOM_H_

//#include <iostream>
#include <random>

class Random {
private:
	std::mt19937_64 rng;
	std::uniform_real_distribution<double> unif;

	Random();

public:
	static Random& getRandomInstance();
	int getInt(int upperBound);
};

#endif /* HELPERS_RANDOM_H_ */

//int main() {
//	for(int i=0; i<30; i++)
//		std::cout<<Random::getRandomInstance().getInt(10)<<std::endl;
//}
