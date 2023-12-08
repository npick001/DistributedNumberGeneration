#include "NumberGeneration.h"

void RandomTreeGeneration()
{
	// create a vector of LCGs
	// the new LCG's are created from the left_generator's numberstream as the
	// seed and the multiplier is a^(COMM_WORLD_SIZE)
	const int num_processors = 4;
	vector<LCG*> generators;

	// SERIAL RNG with LCG
	int x0 = 917; // seed
	int a = 65531; // multiplier
	int c = 127; // increment
	int m = static_cast<int>(2E22); // modulus
	int N = 3000; // # of RN to generate

	// create the left generator
	LCG* left_generator = new LCG(x0, a, c, m);
	auto left_stream = left_generator->GetNumberStream(N);

	// generate the right generators
	for (int i = 0; i < num_processors; i++)
	{
		LCG* right_generator = new LCG(left_stream[i].first, a, c, m);
		generators.push_back(right_generator);
	}

	// generate the random numbers from the right generators
	for (int i = 0; i < num_processors; i++)
	{
		string filename = "Output Files\\RANDOM_TREE_proc" + to_string(i) + "_stream.txt";
		generators[i]->WriteStreamToFile(N, filename);
	}

	cout << "Random Tree Generation Complete." << endl;
}

void LeapFrogGeneration()
{
	// create a new vector of LCG's
	// the new LCG's are created from the left_generator's numberstream as the
	// seed, but this method ensures no number overlap between the generators
	const int num_processors = 4;
	vector<LCG*> generators;

	// SERIAL RNG with LCG
	int x0 = 917; // seed
	int a = 65531; // multiplier
	int c = 127; // increment
	int m = static_cast<int>(2E22); // modulus
	int N = 3000; // # of RN to generate

	// create the left generator
	LCG* left_generator = new LCG(x0, a, c, m);
	auto left_stream = left_generator->GetNumberStream(N);

	// generate the right generators using the leap frog method
	for (int i = 0; i < num_processors; i++)
	{
		LCG* right_generator = new LCG(left_stream[i].first, a, c, m);
		right_generator->SetGenerationLag(num_processors, i);
		generators.push_back(right_generator);
	}

	// generate the random numbers from the right generators
	for (int i = 0; i < num_processors; i++)
	{
		string filename = "Output Files\\LEAP_FROG_proc" + to_string(i) + "_stream.txt";
		generators[i]->WriteStreamToFile(N, filename);
	}

	cout << "Leap Frog Generation Complete." << endl;
}
