#pragma once
#include "Utility.h"

// define the Linear Congruential Generator (LCG) class
class LCG
{
public:
	LCG(int seed, int a, int c, int m);
	LCG(LCG& other);

	void WriteStreamToFile(int N, std::string filename) const;
	void SetGenerationLag(int lag);

	double GetNumber(int position) const;
	std::vector<std::pair<int, double>> GetNumberStream(int N) const;

	int GetSeed() const;
	int GetMultiplier() const;
	int GetIncrement() const;
	int GetModulus() const;

	bool operator==(const LCG& other) const;
	bool operator!=(const LCG& other) const;

private:
	int m_a;
	int m_c;
	int m_m;
	int m_N;
	int m_seed;

	int m_lag;
	int m_startingPosition;
};

