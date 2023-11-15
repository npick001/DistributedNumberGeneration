#pragma once
#include "Utility.h"
#include "LCG.h"

// use the random tree method to generate N random number generators
std::vector<LCG*> RandomTreeGeneration(LCG* left_gen, int num_generators);

// use the leap frog method to generate N random number stream
std::vector<LCG*> LeapFrogGeneration(LCG* left_gen, int N);