#include "NumberGeneration.h"

void RandomTreeGeneration(LCG left_generator, int stream_length, int processors)
{
	auto left_stream = left_generator.GetNumberStream(processors + 1);

	// generate the right generators
	for (int i = 0; i < processors; i++)
	{
		string filename = "Output Files\\RANDOM_TREE_proc" + to_string(i) + "_stream.txt";
		cout << "Creating generator " << i << " with seed " << left_stream[i].first << endl;

		auto a = left_generator.GetMultiplier();
		auto c = left_generator.GetIncrement();
		auto m = left_generator.GetModulus();

		LCG* right_generator = new LCG(left_stream[i].first, a, c, m);
		right_generator->WriteStreamToFile(stream_length, filename);

		delete right_generator;
	}

	cout << "Random Tree Generation Complete." << endl;
}

void LeapFrogGeneration(LCG left_generator, int stream_length, int processors)
{
	auto left_stream = left_generator.GetNumberStream(processors + 1);

	// generate the right generators using the leap frog method
	for (int i = 0; i < processors; i++)
	{
		string filename = "Output Files\\LEAP_FROG_proc" + to_string(i) + "_stream.txt";
		auto a = left_generator.GetMultiplier();
		auto c = left_generator.GetIncrement();
		auto m = left_generator.GetModulus();

		LCG* right_generator = new LCG(left_stream[i].first, a, c, m);
		right_generator->SetGenerationLag(processors, i);
		right_generator->WriteStreamToFile(stream_length, filename);

		delete right_generator;
	}

	cout << "Leap Frog Generation Complete." << endl;
}
