#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;

vector<vector<int>>  readInFile(string);
int scoreBridge(const vector<vector<int>>&);
ostream& operator<<(ostream&, const vector<vector<int>>&);
vector<vector<int>> findPossibleBridgeScoresAndLengths(const vector<vector<int>>&, int);

int main()
{
	string myfilename = "input.txt";
	vector<vector<int>> myComponents = readInFile(myfilename);
	vector<vector<int>> bridgeScoresAndLengths = findPossibleBridgeScoresAndLengths(myComponents, 0);
	int longestBridgeLength = (*max_element(bridgeScoresAndLengths.begin(), bridgeScoresAndLengths.end(), [](vector<int> sL1, vector<int> sL2) {return sL1[1] < sL2[1];}))[1];
	vector<vector<int>> longestBridges(bridgeScoresAndLengths.size(),vector<int>(2,0));
	copy_if(bridgeScoresAndLengths.begin(), bridgeScoresAndLengths.end(), longestBridges.begin(), [longestBridgeLength](vector<int> sL) { return sL[1] == longestBridgeLength; });
	int strongestLongestBridgeScore = (*max_element(longestBridges.begin(), longestBridges.end(), [](vector<int> sL1, vector<int> sL2) {return sL1[0] < sL2[0];}))[0];

	cout << strongestLongestBridgeScore << endl;

	cin.get();
	return 0;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& components)
{
	for (int i = 0; i < components.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			os << components[i][j] << '\t';
		}
		os << endl;
	}
	os << endl;

	return os;
}

vector<vector<int>> findPossibleBridgeScoresAndLengths(const vector<vector<int>>& components, int toMatch)
{
	vector<vector<int>> scoresAndLengths(0);
	for (int i = 0; i < components.size(); i++)
	{
		vector<int> component = components[i];
		auto matchPos = find(component.begin(), component.end(), toMatch);
		if (matchPos != component.end())
		{
			int nextToMatch;
			if (matchPos == component.begin())
			{
				nextToMatch = *(component.begin() + 1);
			}
			else
			{
				nextToMatch = *component.begin();
			}

			int scoreOfThisComponent = component[0] + component[1];
			vector<vector<int>> componentsLeft = components;
			componentsLeft.erase(componentsLeft.begin() + i);
			vector<vector<int>> branchScoresAndLengths = findPossibleBridgeScoresAndLengths(componentsLeft, nextToMatch);
			scoresAndLengths.push_back({ scoreOfThisComponent, 1 });
			for (vector<int> branchScoreAndLength : branchScoresAndLengths)
			{
				scoresAndLengths.push_back({ scoreOfThisComponent + branchScoreAndLength[0], branchScoreAndLength[1] + 1 });
			}
		}

	}
	return scoresAndLengths;
}

vector<vector<int>> readInFile(string myfilename)
{
	ifstream myfile(myfilename);
	vector<vector<int>> components(0);
	string line;
	while (getline(myfile, line))
	{
		istringstream linestream(line);
		vector<int> thisComponent(0);
		string temp;
		while (getline(linestream, temp, '/'))
		{
			thisComponent.push_back(stoi(temp));
		}
		components.push_back(thisComponent);
	}

	return components;
}

int scoreBridge(const vector<vector<int>>& bridge)
{
	int score = 0;
	for (vector<int> component : bridge)
	{
		score += component[0] + component[1];
	}
	return score;
}
