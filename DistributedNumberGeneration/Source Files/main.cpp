#include "NumberGeneration.h"

using namespace std;

int main() {

	// SERIAL RNG with LCG
	constexpr unsigned long long m = 2147483647; // 2^31 - 1
	constexpr int a = 48271;      // multiplier
	constexpr unsigned long long c = 1; // Increment
	constexpr int x0 = 12345;       // seed 
	constexpr int N = 3000; // # of RN to generate
	constexpr int processors = 4; // # of processors to use

	// create the left generator
	LCG* left_generator = new LCG(x0, a, c, m);

	cout << "Random Tree Generation: " << endl;
	RandomTreeGeneration(*left_generator, N, processors);

	cout << endl;

	cout << "Leap Frog Generation: " << endl;
	LeapFrogGeneration(*left_generator, N, processors);

	return 0;
}