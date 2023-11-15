#include "LCG.h"

LCG::LCG(int seed, int a, int c, int m)
{
    m_seed = seed;
	m_a = a;
	m_c = c;
	m_m = m;
	m_N = 1;

    m_lag = -1;
    m_startingPosition = -1; // THIS SHOULD CALL COMMUNICATIONRANK()
}

LCG::LCG(LCG& other)
{
    m_seed = other.m_seed;
	m_a = other.m_a;
	m_c = other.m_c;
	m_m = other.m_m;
	m_N = other.m_N;

    m_lag = other.m_lag;
    m_startingPosition = other.m_startingPosition;
}

void LCG::WriteStreamToFile(int N, std::string filename) const
{
    std::ofstream file(filename);

    if (!file.good())
    {
        std::cout << "ERROR OPENING FILE: " << filename << std::endl;
        return;
    }

    auto stream = GetNumberStream(N);
    std::string data = "x_i,r_i\n";

    for(auto pair : stream)
	{
		data += std::to_string(pair.first) + "," + std::to_string(pair.second) + '\n';
	}

	file << data;
	file.close();
}

void LCG::SetGenerationLag(int lag)
{
	m_N = lag;
}

double LCG::GetNumber(int position) const
{
    // use the number stream such that the last element is the number
    // the user asked for.
    std::vector<std::pair<int, double>> stream = GetNumberStream(position + 1);
    return stream[position].second;
}

std::vector<std::pair<int, double>> LCG::GetNumberStream(int N) const
{
    int x = m_seed;
    std::vector<std::pair<int, double>> stream;

    if (m_lag < 0) {
        for (int i = 0; i < N; i++) {
            int current = (m_a * x + m_c) % m_m;
            double real_number = static_cast<double>(current) / m_m;

            stream.push_back(std::make_pair(current, real_number));
            x = current;   
        }
    }
    else {

        int new_N = N * m_lag;

        // REPLACE i START WITH THE STARTING POSITION
        for (int i = 0; i < new_N; i++) {
            
            // ALSO REPLACE == CONDITION WITH STARTING POSITION
            if (i % m_lag == 0) {
				int current = (m_a * x + m_c) % m_m;
				double real_number = static_cast<double>(current) / m_m;

				stream.push_back(std::make_pair(current, real_number));
				x = current;   
			}
            else {
                int current = (m_a * x + m_c) % m_m;
                x = current;
            }
        }
    }

    return stream;
}

int LCG::GetSeed() const
{
    return m_seed;
}

int LCG::GetMultiplier() const
{
    return m_a;
}

int LCG::GetIncrement() const
{
    return m_c;
}

int LCG::GetModulus() const
{
    return m_m;
}

bool LCG::operator==(const LCG& other) const
{
    if (m_a == other.m_a && m_c == other.m_c && m_m == other.m_m && m_N == other.m_N)
    {
		return true;
    }

    return false;
}

bool LCG::operator!=(const LCG& other) const
{
    return !(*this == other);
}
