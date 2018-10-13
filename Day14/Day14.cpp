#include <iostream>
#include <vector>
#include <sstream>
#include <ios>
#include <bitset>
using namespace std;

constexpr int NUMBER_OF_ROWS = 128;
constexpr int BITS_PER_ROW = 128;
constexpr int BITS_PER_HEX = 4;

string performKnotHash(string&);
string stringdashint(string, int);
string hexStringToBitString(string&);
vector<string> findSquare(string&);
int countUsedSquares(vector<string> &);
int findNumberOfGroups(vector<string>&);
void accountForGroup(vector<vector<bool>>&, const vector<string>&, int, int);

int main() {
	
	//string inputString = "flqrgnkx";
	string inputString = "hfdlxzhv";
	vector<string> theSquare = findSquare(inputString);
	int usedSquares = countUsedSquares(theSquare);
	cout << "num used squares = " << usedSquares << endl;
	int numGroups = findNumberOfGroups(theSquare);
	cout << "number of groups = " << numGroups << endl;

	cin.get();
	return 0;
}


string performKnotHash(string& inputString)
{
	// initialise lengths
	vector<int> inputLengths(inputString.length());
	for (int i = 0; i < inputString.length(); i++) {
		inputLengths[i] = int(inputString[i]);
	}
	vector<int> standardAddOn = { 17, 31, 73, 47, 23 };
	inputLengths.insert(inputLengths.end(), standardAddOn.begin(), standardAddOn.end());

	// initialise list
	int listSize = 256;
	vector<int> theList(listSize);
	for (int i = 0; i < listSize; i++) {
		theList[i] = i;
	}

	// 64 rouds of reordering stuff
	int currentPos = 0, skipSize = 0;
	for (int round = 0; round < 64; round++) {

		for (int len : inputLengths) {
			vector<int> toReverse(len);
			for (int i = 0; i < len; i++) {
				toReverse[i] = theList[(currentPos + i) % listSize];
			}
			reverse(toReverse.begin(), toReverse.end());
			for (int i = 0; i < len; i++) {
				theList[(currentPos + i) % listSize] = toReverse[i];
			}
			currentPos = (currentPos + len + skipSize) % listSize;
			skipSize++;

		}

	}

	// sparse hash -> desnse hash
	vector<int> denseHash(16);
	for (int i = 0; i < 16; i++) {

		int hashElem = theList[i * 16];
		for (int j = i * 16 + 1; j < (i + 1) * 16; j++) {
			hashElem ^= theList[j];
		}
		denseHash[i] = hashElem;
	}

	stringstream ss;
	string hexstr;
	for (int i : denseHash) {
		stringstream hexss;
		hexss << hex << i;
		hexstr = hexss.str();
		if (hexstr.length() == 1) {
			ss << '0';
		}
		ss << hexstr;
	}

	return ss.str();
}

string stringdashint(string theString, int theInt)
{
	stringstream ss;
	ss << theString << '-' << theInt;

	return ss.str();
}

string hexStringToBitString(string& hexString)
{
	stringstream bitstringstream;
	for (char c : hexString)
	{
		stringstream ss;
		ss << hex << c;

		int decTranslation;
		ss >> decTranslation;
		bitset<BITS_PER_HEX> b(decTranslation);
		bitstringstream << b;
	}

	return bitstringstream.str();
}

vector<string> findSquare(string & inputString)
{
	vector<string> theSquare(128);
	string hexKnotHash;

	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		string rowInput = stringdashint(inputString, i);
		hexKnotHash = performKnotHash(rowInput);
		string bitKnotHash = hexStringToBitString(hexKnotHash);
		theSquare[i] = bitKnotHash;
		
	}
	return theSquare;
}

int countUsedSquares(vector<string> & theSquare)
{
	int usedSquares = 0;
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		usedSquares += count(theSquare[i].begin(), theSquare[i].end(), '1');
	}
	return usedSquares;
}

int findNumberOfGroups(vector<string>& theSquare)
{
	vector<vector<bool>> accountedFor(NUMBER_OF_ROWS);
	for (int i = 0; i < NUMBER_OF_ROWS; i++)
	{
		vector<bool> tempVec(BITS_PER_ROW, false);
		accountedFor[i] = tempVec;
	}
	int numGroups = 0;
	for (int row = 0; row < NUMBER_OF_ROWS; row++)
	{
		string rowString = theSquare[row];
		for (int bit = 0; bit < BITS_PER_ROW; bit++)
		{
			if (rowString[bit] == '1' && !accountedFor[row][bit])
			{
				accountForGroup(accountedFor, theSquare, row, bit);
				numGroups++;
			}
		}
	}
	return numGroups;
}

void accountForGroup(vector<vector<bool>>& accountedFor, const vector<string>& theSquare, int row, int col)
{
	accountedFor[row][col] = true;

	if (row != 0 && theSquare[row - 1][col] == '1' && !accountedFor[row-1][col])
	{
		accountForGroup(accountedFor, theSquare, row - 1, col);
	}
	if (row != NUMBER_OF_ROWS - 1 && theSquare[row + 1][col] == '1' && !accountedFor[row + 1][col])
	{
		accountForGroup(accountedFor, theSquare, row + 1, col);
	}
	if (col != 0 && theSquare[row][col-1] == '1' && !accountedFor[row][col-1])
	{
		accountForGroup(accountedFor, theSquare, row, col-1);
	}
	if (col != BITS_PER_ROW - 1 && theSquare[row][col+1] == '1' && !accountedFor[row][col+1])
	{
		accountForGroup(accountedFor, theSquare, row, col+1);
	}
	return;
}

