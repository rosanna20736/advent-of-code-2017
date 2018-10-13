#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<map>
using namespace std;

enum class directionOfTravel
{
	up, left, down, right
};

vector<string> readInFile(const string&);
vector<int> findStart(const vector<string>&);
string traverseTubesAndFindLetters(const vector<string>&, vector<int>);
void goInDirection(vector<int>&, const directionOfTravel);
void changeDirection(const vector<int>, directionOfTravel&, const vector<string>&);

int main()
{
	string myfilename = "input.txt";
	vector<string> theTubes = readInFile(myfilename);
		
	vector<int> startPosition = findStart(theTubes);
	string lettersFound = traverseTubesAndFindLetters(theTubes, startPosition);

	cout << lettersFound << endl;

	cin.get();
	return 0;
}

vector<string> readInFile(const string& myfilename)
{
	ifstream myfile(myfilename);
	vector<string> theTubes(0);
	string line;
	while (getline(myfile, line))
	{
		theTubes.push_back(line);
	}
	return theTubes;
}

vector<int> findStart(const vector<string>& theTubes)
{
	string firstLine = theTubes[0];
	int x = 0;
	for (; x < firstLine.length(); x++)
	{
		if (firstLine[x] == '|')
		{
			break;
		}
	}
	vector<int> startPosition = { x, 0 };

	return startPosition;
}



string traverseTubesAndFindLetters(const vector<string>& theTubes, vector<int> currentPosition)
{
	bool endReached = false;
	directionOfTravel currentDirection = directionOfTravel::down;
	string lettersFound = "";
	int stepsTaken = 0;

	while (!endReached)
	{
		goInDirection(currentPosition, currentDirection);
		stepsTaken++;

		char whatsHere = theTubes[currentPosition[1]][currentPosition[0]];

		if (isupper(whatsHere))
		{
			lettersFound.push_back(whatsHere);
		}
		else if (whatsHere == '+')
		{
			changeDirection(currentPosition, currentDirection, theTubes);
		}
		else if (whatsHere == ' ' || currentPosition[0] < 0 || currentPosition[1] < 0 || currentPosition[0] > theTubes[currentPosition[1]].length() || currentPosition[1] > theTubes.size())
		{
			endReached = true;
		}
	}
	cout << stepsTaken << endl;
	return lettersFound;
}

void goInDirection(vector<int>& currentPosition, const directionOfTravel direction)
{
	switch (direction)
	{
	case directionOfTravel::up:
		currentPosition[1] -= 1;
		return;
	case directionOfTravel::left:
		currentPosition[0] -= 1;
		return;
	case directionOfTravel::down:
		currentPosition[1] += 1;
		return;
	case directionOfTravel::right:
		currentPosition[0] += 1;
		return;
	};
}

void changeDirection(const vector<int> currentPosition, directionOfTravel& direction, const vector<string>& theTubes)
{
	vector<char> upLeftDownRightChars(4);
	if (currentPosition[1] - 1 > 0)
	{
		upLeftDownRightChars[0] = theTubes[currentPosition[1] - 1][currentPosition[0]];
	}
	else
	{
		upLeftDownRightChars[0] = ' ';
	}
	if (currentPosition[0] - 1 > 0)
	{
		upLeftDownRightChars[1] = theTubes[currentPosition[1]][currentPosition[0] - 1];
	}
	else
	{
		upLeftDownRightChars[1] = ' ';
	}
	if (currentPosition[1] + 1 < theTubes.size())
	{
		upLeftDownRightChars[2] = theTubes[currentPosition[1] + 1][currentPosition[0]];
	}
	else
	{
		upLeftDownRightChars[2] = ' ';
	}
	if (currentPosition[0] + 1 < theTubes[currentPosition[1]].length())
	{
		upLeftDownRightChars[3] = theTubes[currentPosition[1]][currentPosition[0] + 1];
	}
	else
	{
		upLeftDownRightChars[3] = ' ';
	}

	vector<bool> isPathUpLeftDownRight = {
		upLeftDownRightChars[0] == '|' || isupper(upLeftDownRightChars[0]) ,
		upLeftDownRightChars[1] == '-' || isupper(upLeftDownRightChars[1]),
		upLeftDownRightChars[2] == '|' || isupper(upLeftDownRightChars[2]),
		upLeftDownRightChars[3] == '-' || isupper(upLeftDownRightChars[3])
	};

	if (isPathUpLeftDownRight[0] && direction != directionOfTravel::down)
	{
		direction = directionOfTravel::up;
		return;
	}
	else if (isPathUpLeftDownRight[1] && direction != directionOfTravel::right)
	{
		direction = directionOfTravel::left;
		return;
	}
	else if (isPathUpLeftDownRight[2] && direction != directionOfTravel::up)
	{
		direction = directionOfTravel::down;
		return;
	}
	else if (isPathUpLeftDownRight[3] && direction != directionOfTravel::left)
	{
		direction = directionOfTravel::right;
		return;
	}
	else
	{
		cout << "direction error" << endl;
		return;
	}

}
