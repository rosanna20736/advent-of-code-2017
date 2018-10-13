#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

struct numSpecifier {
	int numRows;
	int numCols;
};

numSpecifier getNumRowsCols(const string& filename)
{
	numSpecifier returnSpec;

	ifstream myfile(filename);
	string line;

	returnSpec.numRows = 0;
	int i = 0;
	while(getline(myfile,line))
	{
		returnSpec.numRows++;
		if (i == 0) {
			returnSpec.numCols = 0;
			istringstream iss(line);
			string a;
			while (iss) {
				iss >> a;
				returnSpec.numCols++;
			}
			returnSpec.numCols--;
		}

	}
	
	myfile.close();
	return returnSpec;
}

void printArray(const int numRows, const int numCols, int** myArray)
{
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			cout << myArray[row][col] << '\t';
		}
		cout << '\n';
	}

}

int main()
{
	string myFilename = "day2input.txt";

	numSpecifier numRowsCols = getNumRowsCols(myFilename);
	int numRows = numRowsCols.numRows;
	int numCols = numRowsCols.numCols;

	ifstream myfile(myFilename);
	string line;

	// load in values from file to myArray
	int** myArray = new int*[numRows];
	for (int row = 0; row < numRows; row++)
	{
		myArray[row] = new int[numCols];
		getline(myfile, line);
		istringstream iss(line);
		for (int col = 0; col < numCols; col++)
		{
			iss >> myArray[row][col];
		}
	}

	// find sum of max_element - min_element of each of the rows
	int checkSum = 0;
	for (int row = 0; row < numRows; row++)
	{
		int rowMax = *max_element(myArray[row], myArray[row] + numCols);
		int rowMin = *min_element(myArray[row], myArray[row] + numCols);
		
		checkSum += (rowMax - rowMin);
	}

	cout << checkSum << endl;

	int newCheckSum = 0;
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++) {
			for (int col2 = 0; col2 < numCols; col2++) {

				if (myArray[row][col] % myArray[row][col2] == 0 && col != col2)
				{
					newCheckSum += myArray[row][col] / myArray[row][col2];
					break;
				}

			}
		}
	}

	cout << newCheckSum;

	for (int row = 0; row < numRows; row++)
	{
		delete[] myArray[row];
	}
	delete[] myArray;

	cin.get();
	return 0;
}