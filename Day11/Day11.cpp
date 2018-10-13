#include <iostream>
#include  <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<string> toVectorOfStrings(string);
vector<int> movePos(vector<int>&, const string&);
int findDistance(vector<int>);


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
	string myInput;
	ifstream myfile("input.txt");
	getline(myfile, myInput);
	//string myInput = "ne,ne,s,s";
	vector<int> myPos(3);
	int maxDist = 0, thisDist;

	vector<string> instructions = toVectorOfStrings(myInput);

	for (string instruction : instructions) {
		myPos = movePos(myPos, instruction);
		thisDist = findDistance(myPos);
		if (thisDist > maxDist) { maxDist = thisDist; }
	}

	int distFromStart = findDistance(myPos);
	cout << "distance = " << distFromStart << endl;
	cout << "max distance = " << maxDist << endl;


}

vector<string> toVectorOfStrings(string myString)
{
	vector<string> parsedVec;
	string holdingString;

	for (char c : myString) {
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

vector<int> movePos(vector<int>& myPos, const string& toMove)
{

	if (toMove == "n")
	{
		myPos[1]++;
		myPos[2]--;
	}
	else if (toMove == "ne")
	{
		myPos[0]++;
		myPos[2]--;
	}
	else if (toMove == "se")
	{
		myPos[0]++;
		myPos[1]--;
	}
	else if (toMove == "s")
	{
		myPos[1]--;
		myPos[2]++;
	}
	else if (toMove == "sw")
	{
		myPos[0]--;
		myPos[2]++;
	}
	else if (toMove == "nw")
	{
		myPos[0]--;
		myPos[1]++;
	}
	else
	{
		cout << "invalid instruction" << endl;
	}
	return myPos;
}

int findDistance(vector<int> myPos)
{
	int mySum = 0;
	for (int i : myPos)
	{
		mySum += abs(i);
	}
	return mySum/2;
}
