#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct reg {
	string name;
	int value;
};

reg& FindReg(vector<reg>& regList, const string& regName) {
	for (int i = 0; i < regList.size(); i++) {
		if (regList[i].name == regName) {
			return regList[i];
		}
	}
}

bool CompareRegValues(reg reg1, reg reg2) {
	return reg1.value < reg2.value;
}

int LargestRegisterValue(const vector<reg>& regList) {
	return (*max_element(regList.begin(), regList.end(), CompareRegValues)).value;
}

void printRegisters(vector<reg> regList) {
	for (reg regi : regList) {
		cout << regi.name << ": " << regi.value << '\t';
	}
	cout << endl;
}

int main() {

	string filename = "input.txt";
	ifstream myfile;
	myfile.open(filename);

	// get data from file into vector of register names
	string line;
	vector<reg> registerList;
	vector<string> registerNames;
	while (getline(myfile, line))
	{
		istringstream iss(line);
		string a;
		iss >> a;
		if (count(registerNames.begin(), registerNames.end(),a) == 0) {
			reg tempReg;
			registerNames.push_back(a);
			tempReg.name = a;
			tempReg.value = 0;
			registerList.push_back(tempReg);
		}
	}

	vector<int> registerVals (registerList.size(), 0);
	myfile.close(); // go back to beginning of the file
	myfile.open(filename);

	int LargestEverValue = 0;

	while (getline(myfile, line))
	{
		// read in informaiton
		istringstream iss(line);
		string temp;
		string regToChange;
		string incOrDec;
		string checkReg;
		string condition;
		iss >> regToChange;
		iss >> incOrDec;
		iss >> temp;
		int incOrDecAmount = stoi(temp);
		iss >> temp; // "if"
		iss >> checkReg;
		iss >> condition;
		iss >> temp;
		int conditionVal = stoi(temp);
		bool conditionSatisfied;

		// check if the condition is satisfied
		if (condition == "==") {
			conditionSatisfied = FindReg(registerList, checkReg).value == conditionVal;
		}
		else if (condition == "!=") {
			conditionSatisfied = FindReg(registerList, checkReg).value != conditionVal;
		}
		else if (condition == "<") {
			conditionSatisfied = FindReg(registerList, checkReg).value < conditionVal;
		}
		else if (condition == ">") {
			conditionSatisfied = FindReg(registerList, checkReg).value > conditionVal;
		}
		else if (condition == "<=") {
			conditionSatisfied = FindReg(registerList, checkReg).value <= conditionVal;
		}
		else if (condition == ">=") {
			conditionSatisfied = FindReg(registerList, checkReg).value >= conditionVal;
		}
		else {
			cout << "Error: condition = " << condition << endl;
		}

		// perform the increment/decrement if the condition is satisfied
		if (conditionSatisfied) {
			if (incOrDec ==  "inc") {
				FindReg(registerList, regToChange).value += incOrDecAmount;
			}
			else if (incOrDec == "dec") {
				FindReg(registerList, regToChange).value -= incOrDecAmount;
			}
			else {
				cout << "Error: incOrDec = " << incOrDec << endl;
			}
		}

		int LargestVal = LargestRegisterValue(registerList);
		if (LargestVal > LargestEverValue) {
			LargestEverValue = LargestVal;
		}
	}

	cout << "the largest value is " << LargestRegisterValue(registerList) << endl;
	cout << "the largest EVER value is " << LargestEverValue << endl;

	cin.get();
	return 0;
}