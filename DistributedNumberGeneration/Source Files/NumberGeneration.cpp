#include "NumberGeneration.h"

std::vector<LCG*> RandomTreeGeneration(LCG* left_gen, int num_generators)
{
	// create a vector of LCGs
	// the new LCG's are created from the left_generator's numberstream as the
	// seed and the multiplier is a^(COMM_WORLD_SIZE)


	return std::vector<LCG*>();
}

std::vector<LCG*> LeapFrogGeneration(LCG* left_gen, int N)
{
	// create a new vector of LCG's
	// the new LCG's are created from the left_generator's numberstream as the
	// seed, but this method ensures no number overlap between the generators


	return std::vector<LCG*>();
}
