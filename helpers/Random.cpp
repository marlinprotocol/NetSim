#include "Random.h"

Random::Random() : unif(0, 1) {
	// initiaze random number generator, seed fixed to 2121 to make it deterministic across runs
	// else make it time-dependent for randomness
	uint64_t seed = 937;
	std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed>>32)};
	rng.seed(ss);
}

Random& Random::getRandomInstance() {
	static Random random;
	return random;
}

int Random::getInt(int upperBound) {
	return (int) (unif(rng) * upperBound);
}
