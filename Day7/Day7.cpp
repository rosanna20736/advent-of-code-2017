#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct program {
	string name;
	int weight;
	vector<string> children;
};

template<class T>
bool ElementsEqual(vector<T> vec) {
	return all_of(vec.begin(), vec.end(), [vec](T i) {return i == vec[0];});
}

program FindProg(vector<program> programList, string progName) {
	for (program prog : programList) {
		if (prog.name == progName) {
			return prog;
		}
	}
}

int FindTreeWeight(vector<program> programList, program startOfTree) {
	int totWeight = startOfTree.weight;

	for (string child : startOfTree.children) {
		program childProg = FindProg(programList, child);
		totWeight += FindTreeWeight(programList, childProg);
	}

	return totWeight;
}

void printProgram(program prog) {
	cout << prog.name << " (" << prog.weight << ") -> ";
	for (string str : prog.children) {
		cout << str << '\t';
	}
	cout << endl;
}

int main() {

	ifstream myfile("input.txt");

	// get data from file into vector of programs
	string line;
	vector<program> programList;

	while (getline(myfile, line))
	{
		program progTemp;
		vector<string> LineStringVec;
		istringstream iss(line);
		string a;
		while (iss >> a) {
			LineStringVec.push_back(a);
		}

		progTemp.name = LineStringVec[0];
		progTemp.weight = stoi(LineStringVec[1].substr(1, LineStringVec[1].length()-2));
		for (int i = 3; i < LineStringVec.size(); i++)
		{
			string childName = LineStringVec[i];
			if (i != (LineStringVec.size() - 1)) {
				childName = childName.substr(0,childName.length()-1);
			}
			progTemp.children.push_back(childName);
		}
		programList.push_back(progTemp);
	}

	// find bottom
	program Bottom;
	for (program prog : programList) {
		bool ImTheBottom = true;
		for (program otherprog : programList) {
			for (string child : otherprog.children) {
				if (child == prog.name) {
					ImTheBottom = false;
					break;
				}
			}
		}
		if (ImTheBottom) {
			cout << "It's me: " << prog.name << "!" << endl;
			Bottom = prog;
		}
		
	}

	program currentProg = Bottom;
	program prevProg;
	int weightDiff;
	bool outlierFound = false;
	while (!outlierFound) {
		vector<int> subTreeWeights;
		for (string child : currentProg.children) {
			program childProg = FindProg(programList, child);
			int TreeWeight = FindTreeWeight(programList, childProg);
			cout << TreeWeight << '\t';
			subTreeWeights.push_back(TreeWeight);
		}
		cout << endl;
		if (ElementsEqual(subTreeWeights)) {
			outlierFound = true;
		}
		else {
			prevProg = currentProg;
			for (int i = 0; i < subTreeWeights.size(); i++) {
				if (count(subTreeWeights.begin(), subTreeWeights.end(), subTreeWeights[i]) == 1) {
					weightDiff = subTreeWeights[i] - subTreeWeights[(i + 1) % subTreeWeights.size()];
					currentProg = FindProg(programList, currentProg.children[i]);
					break;
				}
			}

		}
		
	}
	cout << "weight that needs changing is " << currentProg.name << " which has weight " << currentProg.weight << endl;
	cout << "weight diff is " << weightDiff;
	cout << " so it needs to be " << currentProg.weight - weightDiff << endl;
	
	cin.get();
	return 0;
}