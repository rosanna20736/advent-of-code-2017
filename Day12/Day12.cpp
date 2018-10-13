#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> FileToConnections(ifstream&);
vector<int> findGroupFromConnections(vector<vector<int>>);
vector<vector<int>> findAllGroups(vector<vector<int>>);

template <class T>
void printVector(vector<T> myVec)
{
	for (T i : myVec) {
		cout << i << '\t';
	}
	cout << endl;
}

int main()
{
	ifstream myfile("input.txt");
	vector<vector<int>> theConnections = FileToConnections(myfile);
	vector<vector<int>> theGroups = findAllGroups(theConnections);

	cout << "the number of groups is " << theGroups.size();
}

vector<vector<int>> FileToConnections(ifstream& myfile)
{
	vector<vector<int>> theConnections;
	string line;
	while (getline(myfile, line))
	{
		vector<int> connectionsOfThisProgram;
		istringstream iss(line);
		string a;
		iss >> a; // program number will be same as position in vector so not needed
		iss >> a; // "<->"
		while (iss >> a)
		{
			connectionsOfThisProgram.push_back(stoi(a));
		}
		theConnections.push_back(connectionsOfThisProgram);
	}
	return theConnections;
}

vector<int> findGroupFromConnections(vector<vector<int>> theConnections, int startingPoint)
{
	vector<int> theGroup;
	theGroup.push_back(startingPoint);
	int currentPosInGroup = 0;
	do
	{
		int currentProg = theGroup[currentPosInGroup];
		for (int program : theConnections[currentProg])
		{
			if (!count(theGroup.begin(), theGroup.end(), program))
			{
				theGroup.push_back(program);
			}
		}
		currentPosInGroup++;

	} while (currentPosInGroup < theGroup.size());

	return theGroup;
}

vector<vector<int>> findAllGroups(vector<vector<int>> theConnections)
{
	vector<vector<int>> allGroups;
	int currentProgram = 0;
	do
	{
		bool currentProgramIsInAGroup = count_if(allGroups.begin(), allGroups.end(), [currentProgram](vector<int> const& v) { return count(v.begin(), v.end(), currentProgram); });
		if (!currentProgramIsInAGroup)
		{
			vector<int> groupOfCurrentProgram = findGroupFromConnections(theConnections, currentProgram);
			allGroups.push_back(groupOfCurrentProgram);
		}
		currentProgram++;
	} while (currentProgram < theConnections.size());

	return allGroups;
}
