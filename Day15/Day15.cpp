#include<iostream>
#include <bitset>
#include <vector>
using namespace std;

constexpr long int GENERATOR_A_FACTOR = 16807;
constexpr long int GENERATOR_B_FACTOR = 48271;
constexpr long int DIVIDER = 2147483647;
constexpr int PAIRS_TO_CONSIDER = 5000000;
constexpr long int GENERATOR_A_INITIAL_VALUE = 618;
constexpr long int GENERATOR_B_INITIAL_VALUE = 814;
constexpr int GEN_A_MULTIPLE = 4;
constexpr int GEN_B_MULTIPLE = 8;


int main()
{
	long long int generatorAValue = GENERATOR_A_INITIAL_VALUE;
	long long int generatorBValue = GENERATOR_B_INITIAL_VALUE;
	vector<bitset<16>> generatorAbitsets(PAIRS_TO_CONSIDER);
	vector<bitset<16>> generatorBbitsets(PAIRS_TO_CONSIDER);
	int genAValuesFound = 0, genBValuesFound = 0;
	while (genAValuesFound < PAIRS_TO_CONSIDER)
	{
		generatorAValue = (generatorAValue * GENERATOR_A_FACTOR) % DIVIDER;
		if ((generatorAValue % GEN_A_MULTIPLE) == 0)
		{
			bitset<16> generatorAbitset(generatorAValue);
			generatorAbitsets[genAValuesFound] = generatorAbitset;
			genAValuesFound++;
		}
	}

	int numberOfMatches = 0;
	while (genBValuesFound < PAIRS_TO_CONSIDER)
	{
		generatorBValue = (generatorBValue * GENERATOR_B_FACTOR) % DIVIDER;
		if ((generatorBValue % GEN_B_MULTIPLE) == 0)
		{
			bitset<16> generatorBbitset(generatorBValue);
			if (generatorAbitsets[genBValuesFound] == generatorBbitset)
			{
				numberOfMatches++;
			}
			genBValuesFound++;
		}
	}

	cout << "Number of matches = " << numberOfMatches << endl;

	return 0;
}