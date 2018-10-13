#include<fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<map>
using namespace std;

using square = vector<vector<int>>;

map<square, square> readInFile(string);
vector<int> readRow(string);
map<square, square> expandRulesToIncludeRotationsAndFlips(map<square,square>);
square flipHorizontal(square);
square flipVertical(square);
square rotateSquare(square);
void addRotations(square, square, map<square, square>&);
square actRules(square, map<square, square>&, int);
square extractSubSquare(int, int, square, int);
void insertSubSquare(int, int, square&, square&);
int countOnPixels(const square&);

int main()
{
	string myfilename = "input.txt";
	const int numIterations = 18;
	square initialSquare = { {0,1,0},{0,0,1},{1,1,1} };
	map<square,square> rules = readInFile(myfilename);
	map<square, square> fullRules = expandRulesToIncludeRotationsAndFlips(rules);
	square finalSquare = actRules(initialSquare, fullRules, numIterations);
	int numberOfOnPixels = countOnPixels(finalSquare);

	cout << numberOfOnPixels << endl;
	cin.get();
	return 0;
}

ostream& operator<<(ostream& os, const square& theSquare)
{
	for (int i = 0; i < theSquare.size(); i++)
	{
		for (int j = 0; j < theSquare.size(); j++)
		{
			os << theSquare[i][j] << '\t';
		}
		os << endl;
	}
	os << endl;

	return os;
}

map<square, square> readInFile(string myfilename)
{
	ifstream myfile(myfilename);
	map<square, square> rules;
	string line;
	while (getline(myfile, line))
	{
		string first, second, discard, rowString;
		square firstSquare, secondSquare;
		istringstream iss(line);
		iss >> first >> discard >> second;
		istringstream fiss(first);
		istringstream siss(second);

		while (getline(fiss,rowString,'/'))
		{
			vector<int> row = readRow(rowString);
			firstSquare.push_back(row);
		}

		while (getline(siss, rowString, '/'))
		{
			vector<int> row = readRow(rowString);
			secondSquare.push_back(row);
		}

		rules[firstSquare] = secondSquare;
	}
	
	return rules;
}

vector<int> readRow(string stringToRead)
{
	vector<int> row(0);
	for (char c : stringToRead)
	{
		switch (c)
		{
		case '.':
			row.push_back(0);
			break;
		case '#':
			row.push_back(1);
			break;
		default:
			cout << "char not . or #" << endl;
		}
	}
	return row;
}

map<square, square> expandRulesToIncludeRotationsAndFlips(map<square, square> rules)
{
	map<square, square> fullRules;

	for (auto& entry : rules)
	{
		square originalSquare = entry.first;
		square horFlipSquare = flipHorizontal(originalSquare);
		square vertFlipSquare = flipVertical(originalSquare);
		square transformedSquare = entry.second;
		addRotations(originalSquare, transformedSquare, fullRules);
		addRotations(horFlipSquare, transformedSquare, fullRules);
		addRotations(vertFlipSquare, transformedSquare, fullRules);
	}

	return fullRules;
}

square flipHorizontal(square theSquare)
{
	int squareSize = theSquare.size();
	square newSquare(squareSize, vector<int>(squareSize));
	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			newSquare[i][j] = theSquare[i][squareSize - 1 - j];
		}
	}
	return newSquare;
}

square flipVertical(square theSquare)
{
	int squareSize = theSquare.size();
	square newSquare(squareSize, vector<int>(squareSize));
	for (int i = 0; i < squareSize; i++)
	{
		newSquare[i] = theSquare[squareSize - 1 - i];
	}
	return newSquare;
}

square rotateSquare(square theSquare)
{
	int squareSize = theSquare.size();
	square newSquare(squareSize, vector<int>(squareSize));
	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			newSquare[i][j] = theSquare[squareSize - 1 - j][i];
		}
	}
	return newSquare;
}

void addRotations(square firstSquare, square secondSquare, map<square, square>& fullRules)
{
	fullRules[firstSquare] = secondSquare;
	for (int i = 0; i < 3; i++)
	{
		firstSquare = rotateSquare(firstSquare);
		fullRules[firstSquare] = secondSquare;
	}
	return;
}

square actRules(square theSquare, map<square, square>& theRules, int numIterations)
{
	for (int iter = 0; iter < numIterations; iter++)
	{
		cout << "iter: " << iter << endl;
		int squareSize = theSquare.size();
		int subSquareSize = (squareSize % 2 == 0) ? 2 : 3;
		int numSubSquaresPerRow = squareSize / subSquareSize;
		int newSubSquareSize = subSquareSize + 1;
		int newSquareSize = numSubSquaresPerRow * newSubSquareSize;
		square newSquare(newSquareSize, vector<int>(newSquareSize));
		for (int i = 0; i < numSubSquaresPerRow; i++)
		{
			for (int j = 0; j < numSubSquaresPerRow; j++)
			{
				square subSquare = extractSubSquare(i, j, theSquare, subSquareSize);
				square newSubSquare = theRules[subSquare];
				insertSubSquare(i, j, newSquare, newSubSquare);
			}
		}
		theSquare = newSquare;
	}
	return theSquare;
}

square extractSubSquare(int i, int j, square bigSquare, int subSquareSize)
{
	int startPosi = i * subSquareSize;
	int startPosj = j * subSquareSize;
	square subSquare(subSquareSize, vector<int>(subSquareSize));
	for (int row = 0; row < subSquareSize; row++)
	{
		vector<int> thisRow(bigSquare[startPosi + row].begin() + startPosj, bigSquare[startPosi + row].begin() + startPosj + subSquareSize);
		subSquare[row] = thisRow;
	}

	return subSquare;
}

void insertSubSquare(int i, int j, square& bigSquare, square& subSquare)
{
	int subSquareSize = subSquare.size();
	int startPosi = i * subSquareSize;
	int startPosj = j * subSquareSize;
	for (int m = 0; m < subSquareSize; m++)
	{
		for (int n = 0; n < subSquareSize; n++)
		{
			bigSquare[startPosi + m][startPosj + n] = subSquare[m][n];
		}
	}
	return;
}

int countOnPixels(const square & theSquare)
{
	int sum = 0;
	int squareSize = theSquare.size();
	for (int i = 0; i < squareSize; i++)
	{
		for (int j = 0; j < squareSize; j++)
		{
			sum += theSquare[i][j];
		}
	}
	return sum;
}
