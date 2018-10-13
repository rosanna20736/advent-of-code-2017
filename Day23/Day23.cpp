#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
using namespace std;

using lint = long long int;

class instruction
{
	string instructionType, first, second;


public:
	instruction();
	instruction(const string&);
	void print();

	string getFirst() { return first; }

	bool firstInRegisters(map<char, lint>&);
	void actInstruction(map<char, lint>&, int&, int&);
};

vector<instruction> fileToInstructions(string);
map<char, lint> initialiseRegisters(const vector<instruction>&, int);

int main()
{
	string myfilename = "input.txt";
	vector<instruction> myInstructions = fileToInstructions(myfilename);

	map<char, lint> registers = initialiseRegisters(myInstructions, 0);
	int currentInstruction = 0;
	int mulCount = 0;
	while (currentInstruction >= 0 && currentInstruction < myInstructions.size())
	{
			myInstructions[currentInstruction].actInstruction(registers, currentInstruction, mulCount);
			for (auto x : registers)
			{
				cout << x.first << ": " << x.second << '\t';
			}
			cout << endl;
	}

	cout << "num times mul invoked = " << mulCount << endl;

	cin.get();
	return 0;
}

instruction::instruction()
{
	instructionType = "";
	first = "";
	second = "";
}

instruction::instruction(const string& initialiserString)
{
	istringstream iss(initialiserString);
	iss >> instructionType;
	iss >> first;
	if (!(iss >> second)) {
		second = "";
	}
}

void instruction::print()
{
	cout << instructionType << '\t' << first << '\t' << second << endl;
	return;
}

int extractValue(const string& registerNameorInt, map<char, lint>& registers)
{
	if (isdigit(registerNameorInt.back()))
	{
		return stoi(registerNameorInt);
	}
	else
	{
		return registers[registerNameorInt[0]];
	}
}

bool instruction::firstInRegisters(map<char, lint>& registers)
{
	if (isdigit(first[0]))
	{
		return true;
	}
	else
	{
		if (registers.count(first[0]) == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

}

void instruction::actInstruction(map<char, lint>& registers, int& currentInstruction, int& mulCount)
{
	if (instructionType == "jnz")
	{
		int f = extractValue(first, registers);
		int s = extractValue(second, registers);
		if (f != 0)
		{
			currentInstruction += s;
			return;
		}
		else
		{
			currentInstruction++;
			return;
		}
	}
	else
	{
		if (instructionType == "set")
		{
			registers[first[0]] = extractValue(second, registers);
		}
		else if (instructionType == "sub")
		{
			registers[first[0]] -= extractValue(second, registers);
		}
		else if (instructionType == "mul")
		{
			registers[first[0]] *= extractValue(second, registers);
			mulCount++;
		}
		else
		{
			cout << "error. instructionType = " << instructionType << endl;
		}
		currentInstruction++;
		return;
	}
}

vector<instruction> fileToInstructions(string myfilename)
{
	vector<instruction> myInstructions(0);

	ifstream myfile(myfilename);
	string line;

	while (getline(myfile, line))
	{
		instruction thisInstruction(line);
		myInstructions.push_back(thisInstruction);

	}
	return myInstructions;
}

map<char, lint> initialiseRegisters(const vector<instruction>& instructions, int valueOfp)
{
	map<char, lint> registers;
	for (instruction i : instructions)
	{
		if (!i.firstInRegisters(registers))
		{
			char registerName = i.getFirst()[0];
			if (registerName == 'a')
			{
				registers[registerName] = 1;
			}
			else
			{
				registers[registerName] = 0;
			}
		}
	}
	return registers;
}
