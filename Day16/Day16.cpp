#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
using namespace std;

constexpr int numberOfPrograms = 16;
constexpr int TO_REPEAT = 1000000000;

struct PairOfStrings {
	string first;
	string second;
};

vector<string> FileToInstructions(string);
vector<char> createGroup();
void actInstructionsOnGroup(vector<char>&, const vector<string>&);
void printGroup(const vector<char>&);
void Exchange(vector<char>&, string);
void Partner(vector<char>&, string);
vector<char> Swing(vector<char>&, int);
PairOfStrings splitAtSlash(string);

int main()
{
	const string myfilename = "input.txt";
	vector<string> instructions = FileToInstructions(myfilename);
	vector<char> initialGroup = createGroup();
	vector<char> theGroup = initialGroup;
	int period;
	for (int i = 0; i < TO_REPEAT; i++)
	{
		actInstructionsOnGroup(theGroup, instructions);
		if (theGroup == initialGroup)
		{
			period = i + 1;
			cout << period << endl;
			break;
		}
	}
	int remainder = TO_REPEAT % period;
	theGroup = initialGroup;
	for (int i = 0; i < remainder; i++)
	{
		actInstructionsOnGroup(theGroup, instructions);
	}
	printGroup(theGroup);

	cin.get();
	return 0;
}


vector<string> FileToInstructions(string myString)
{
	ifstream myfile(myString);
	string line;
	getline(myfile, line);
	vector<string> parsedVec;
	string holdingString;

	for (char c : line) {
		if (c == ',')
		{
			parsedVec.push_back(holdingString);
			holdingString.clear();
			continue;
		}
		else {
			holdingString.push_back(c);
		}

	}
	parsedVec.push_back(holdingString);

	return parsedVec;
}

vector<char> createGroup()
{
	vector<char> theGroup(numberOfPrograms);
	for (int i = 0; i < numberOfPrograms; i++)
	{
		theGroup[i] = char(97+i);
	}
	return theGroup;
}

void actInstructionsOnGroup(vector<char>& theGroup, const vector<string>& instructions)
{
	int totalSwing = 0;
	for (string instruction : instructions)
	{
		char type = instruction[0];
		string restOfInstruction = instruction.substr(1, instruction.length() - 1);
		switch (instruction[0])
		{
		case 's':
			theGroup = Swing(theGroup, stoi(restOfInstruction));
			break;
		case 'x':
			Exchange(theGroup, restOfInstruction);
			break;
		case 'p':
			Partner(theGroup, restOfInstruction);
			break;
		default:
			cout << "error" << endl;

		}
	}	

	return;
}

void printGroup(const vector<char>& theGroup)
{
	for (char c : theGroup) cout << c;
	cout << endl;
	return;
}

void Exchange(vector<char>& theGroup, string instruction)
{
	PairOfStrings toSwap = splitAtSlash(instruction);
	int first = stoi(toSwap.first);
	int second = stoi(toSwap.second);
	char temp = theGroup[first];
	theGroup[first] = theGroup[second];
	theGroup[second] = temp;
	return;
}

void Partner(vector<char>& theGroup, string instruction)
{
	PairOfStrings toSwap = splitAtSlash(instruction);
	char first = char(toSwap.first[0]);
	char second = char(toSwap.second[0]);
	auto firstPos = find(theGroup.begin(), theGroup.end(), first);
	auto secondPos = find(theGroup.begin(), theGroup.end(), second);
	*firstPos = second;
	*secondPos = first;
	return;
}

vector<char> Swing(vector<char>& theGroup, int swingAmount)
{
	vector<char> newGroup(numberOfPrograms);
	for (int i = 0; i < numberOfPrograms; i++)
	{
		newGroup[(i + swingAmount) % numberOfPrograms] = theGroup[i];
	}
	return newGroup;
}

PairOfStrings splitAtSlash(string mystring)
{
	string::iterator slashPosition = find(mystring.begin(), mystring.end(), '/');
	string first(mystring.begin(), slashPosition);
	string second(slashPosition + 1, mystring.end());
	return PairOfStrings{ first, second };
}

