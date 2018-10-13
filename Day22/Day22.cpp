#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

enum class facingDirection
{
	up, right, down, left
};

enum class nodeState
{
	clean, weakened, infected, flagged
};

map<vector<int>,nodeState> readInFile(const string&);
facingDirection turnRight(facingDirection);
facingDirection turnLeft(facingDirection);
facingDirection reverseDirection(facingDirection);
void moveForward(vector<int>&, facingDirection);
ostream& operator<< (ostream&, const nodeState&);

int main()
{
	string myfilename = "input.txt";
	int middleOfMap = 12;
	int numIterations = 10000000;
	map<vector<int>, nodeState> nodeMap = readInFile(myfilename);

	int infectionsCaused = 0;
	vector<int> carrierPosition = { middleOfMap, middleOfMap };
	facingDirection carrierDirection = facingDirection::up;
	for (int iter = 0; iter < numIterations; iter++)
	{
		switch (nodeMap[carrierPosition])
		{
		case nodeState::clean:
			carrierDirection = turnLeft(carrierDirection);
			nodeMap[carrierPosition] = nodeState::weakened;
			break;
		case nodeState::weakened:
			nodeMap[carrierPosition] = nodeState::infected;
			infectionsCaused++;
			break;
		case nodeState::infected:
			carrierDirection = turnRight(carrierDirection);
			nodeMap[carrierPosition] = nodeState::flagged;
			break;
		case nodeState::flagged:
			carrierDirection = reverseDirection(carrierDirection);
			nodeMap[carrierPosition] = nodeState::clean;
			break;
		}

		moveForward(carrierPosition, carrierDirection);

		if ((iter % (numIterations/100))==0)
		{
			cout << (iter * 100) / numIterations << endl;
		}
	}

	cout << "infections caused: " << infectionsCaused << endl;

	cin.get();
	return 0;
}

map<vector<int>, nodeState> readInFile(const string& myfilename)
{
	ifstream myfile(myfilename);
	map<vector<int>, nodeState> positionsOfInfectedNodes;
	string line;
	int lineNum = 0;
	while (getline(myfile, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '#')
			{
				positionsOfInfectedNodes[{ lineNum, i }] = nodeState::infected;
			}
		}
		lineNum++;
	}

	return positionsOfInfectedNodes;
}

facingDirection turnRight(facingDirection dir)
{
	switch (dir)
	{
	case facingDirection::up:
		return facingDirection::right;
	case facingDirection::right:
		return facingDirection::down;
	case facingDirection::down:
		return facingDirection::left;
	case facingDirection::left:
		return facingDirection::up;
	}
}

facingDirection turnLeft(facingDirection dir)
{
	switch (dir)
	{
	case facingDirection::up:
		return facingDirection::left;
	case facingDirection::right:
		return facingDirection::up;
	case facingDirection::down:
		return facingDirection::right;
	case facingDirection::left:
		return facingDirection::down;
	}
}

facingDirection reverseDirection(facingDirection dir)
{
	switch (dir)
	{
	case facingDirection::up:
		return facingDirection::down;
	case facingDirection::right:
		return facingDirection::left;
	case facingDirection::down:
		return facingDirection::up;
	case facingDirection::left:
		return facingDirection::right;
	}
}

void moveForward(vector<int>& position, facingDirection dir)
{
	switch (dir)
	{
	case facingDirection::up:
		position[0]--;
		return;
	case facingDirection::right:
		position[1]++;
		return;
	case facingDirection::down:
		position[0]++;
		return;
	case facingDirection::left:
		position[1]--;
		return;
	}
}

ostream& operator<< (ostream& os, const nodeState& ns)
{
	switch (ns)
	{
	case nodeState::clean:
		os << "clean";
		return os;
	case nodeState::weakened:
		os << "weakened";
		return os;
	case nodeState::infected:
		os << "infected";
		return os;
	case nodeState::flagged:
		os << "flagged";
		return os;
	}
}
