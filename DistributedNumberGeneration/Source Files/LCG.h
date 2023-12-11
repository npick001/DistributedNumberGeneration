#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/**
 * @brief Writes the given data to a file.
 *
 * This template function writes a single item of any type to a specified file, with two possible write modes:
 * - Append mode (openMode=0): appends the given data to the end of the file if it exists; creates the file if it does not exist.
 * - Truncate mode (openMode=1): overwrites the file with the given data if the file exists; creates the file if it does not exist.
 *
 * @tparam T The type of the data to write to the file. The type must support the insertion operator (operator<<).
 * @param filename The name of the file (with path if needed) where the data is to be written.
 * @param data The data item to write to the file.
 * @param openMode The mode to open the file. 0 represents append mode, and 1 represents truncate mode.
 */
template <typename T>
void WriteToFile(string filename, T data, int openMode) {

	ofstream outfile;

	switch (openMode) {
	case 0:
		outfile.open(filename, ios_base::app);
		break;
	case 1:
		outfile.open(filename, ios_base::trunc);
		break;
	}

	if (!outfile.is_open()) {
		cout << filename << " WAS UNABLE TO OPEN. " << endl;
	}

	outfile << data << '\n';
	outfile.close();
}

// define the Linear Congruential Generator (LCG) class
class LCG
{
public:
	LCG(int seed, int a, unsigned long long c, unsigned long long m);
	LCG(LCG& other);

	void WriteStreamToFile(int N, string filename) const;
	void SetGenerationLag(int lag, int starting_position);

	double GetNumber(int position) const;
	vector<pair<int, double>> GetNumberStream(int N) const;

	int GetSeed() const;
	int GetMultiplier() const;
	int GetIncrement() const;
	long long GetModulus() const;

	bool operator==(const LCG& other) const;
	bool operator!=(const LCG& other) const;

private:
	int m_a;
	unsigned long long m_c;
	unsigned long long m_m;
	int m_N;
	int m_seed;

	int m_lag;
	int m_startingPosition;
};

