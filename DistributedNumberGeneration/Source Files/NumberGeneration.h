#pragma once
#include "LCG.h"

// use the random tree method to generate N random number generators
void RandomTreeGeneration(LCG left_generator, int stream_length, int processors);

// use the leap frog method to generate N random number stream
void LeapFrogGeneration(LCG left_generator, int stream_length, int processors);