#include "NumberGeneration.h"

int main() {

	std::string filename = "Output Files\\random_numbers.txt";

	// SERIAL RNG with LCG
	int x0 = 917; // seed
	int a = 65531; // multiplier
	int c = 127; // increment
	int m = 2E22; // modulus
	int N = 3000; // # of RN to generate

	LCG* left_generator = new LCG(x0, a, c, m);
	left_generator->WriteStreamToFile(N, filename);

	return 0;
}