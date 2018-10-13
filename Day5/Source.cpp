#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main() {

	ifstream myfile("input.txt");
	string line;
	vector<int> jumpOffsets;
	while (getline(myfile, line))
	{
		istringstream iss(line);
		string a;
		iss >> a;
		jumpOffsets.push_back(stoi(a));
	}

	int currentPos = 0;
	int stepsTaken = 0;

	while (currentPos >= 0 && currentPos < jumpOffsets.size())
	{
		int oldPos = currentPos;
		currentPos += jumpOffsets[currentPos];
		if (jumpOffsets[oldPos] >= 3)
		{
			jumpOffsets[oldPos] --;
		}
		else {
			jumpOffsets[oldPos] ++;
		}
		stepsTaken++;

	}

	cout << stepsTaken;

	cin.get();
	return 0;
}