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
	void actInstruction(map<char, lint>&, int&, bool&, vector<lint>&, vector<lint>&, int&);
};

vector<instruction> fileToInstructions(string);
map<char, lint> initialiseRegisters(const vector<instruction>&, int);

int main ()
{
	string myfilename = "input.txt";
	vector<instruction> myInstructions = fileToInstructions(myfilename);

	map<char, lint> registers0 = initialiseRegisters(myInstructions, 0);
	map<char, lint> registers1 = initialiseRegisters(myInstructions, 1);
	int currentInstruction0 = 0, currentInstruction1 = 0;
	int sendCount0 = 0, sendCount1 = 0;
	vector<lint> sentBy0(0), sentBy1(0);
	bool deadlock = false, waiting0 = false, waiting1 = false;
	while (currentInstruction0 >= 0 && currentInstruction0 < myInstructions.size() && currentInstruction1 >= 0 && currentInstruction1 < myInstructions.size() && !deadlock)
	{
		while (currentInstruction0 >= 0 && currentInstruction0 < myInstructions.size() && !waiting0)
		{
			myInstructions[currentInstruction0].actInstruction(registers0, currentInstruction0, waiting0, sentBy0, sentBy1, sendCount0);
			if (!sentBy0.empty())
			{
				waiting1 = false;
			}
		}
		while (currentInstruction1 >= 0 && currentInstruction1 < myInstructions.size() && !waiting1)
		{
			myInstructions[currentInstruction0].actInstruction(registers0, currentInstruction0, waiting1, sentBy1, sentBy0, sendCount1);
			if (!sentBy1.empty())
			{
				waiting0 = false;
			}
		}
		deadlock = waiting0 && waiting1;
	}

	cout << "num times 1 sends = " << sendCount1 << endl;

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

void instruction::actInstruction(map<char, lint>& registers, int& currentInstruction, bool& waiting, vector<lint>& sendingQueue, vector<lint>& recievingQueue, int& sentCount)
{
	if (instructionType == "jgz")
	{
		int f = extractValue(first, registers);
		int s = extractValue(second, registers);
		if (extractValue(first, registers) > 0)
		{
			currentInstruction += extractValue(second, registers);
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
		if (instructionType == "snd")
		{
			sentCount++;
			sendingQueue.push_back(extractValue(first, registers));
		}
		else if (instructionType == "set")
		{
			registers[first[0]] = extractValue(second, registers);
		}
		else if (instructionType == "add")
		{
			registers[first[0]] += extractValue(second, registers);
		}
		else if (instructionType == "mul")
		{
			registers[first[0]] *= extractValue(second, registers);
		}
		else if (instructionType == "mod")
		{
			registers[first[0]] %= extractValue(second, registers);
		}
		else if (instructionType == "rcv")
		{
			if (extractValue(first, registers) != 0)
			{
				if (recievingQueue.empty())
				{
					waiting = true;
					return;
				}
				else
				{
					registers[first[0]] = recievingQueue[0];
					recievingQueue.erase(recievingQueue.begin());
				}

			}
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
			if (registerName == 'p')
			{
				registers[registerName] = valueOfp;
			}
			else
			{
				registers[registerName] = 0;
			}
		}
	}
	return registers;
}
