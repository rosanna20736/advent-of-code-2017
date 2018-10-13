#include <iostream>
using namespace std;

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

int main() {

	const int squareSize = 5;

	int myArray[squareSize][squareSize];

	int startPos = squareSize / 2;
	myArray[startPos][startPos] = 1;

	return 0;
}