#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int Score(int nestingLevel, string group) {
	int totScore = nestingLevel;

	int groupDetector = 0;
	int startOfSubgroup = 1, endOfSubgroup;
	string subgroup;
	for (int i = 1; i < group.length()-1; i++) {
		if (group[i] == ',') {
			continue;
		}
		if (group[i] == '{') {
			groupDetector++;
		}
		else if (group[i] == '}') {
			groupDetector--;
		}
		if (groupDetector == 0) {
			endOfSubgroup = i;

			subgroup = group.substr(startOfSubgroup, endOfSubgroup - startOfSubgroup + 1);
			totScore += Score(nestingLevel + 1, subgroup);

			startOfSubgroup = endOfSubgroup + 2;
		}
	}
	return totScore;
}



int main() {

	//string inputString = "{<>,<{}}>} ";
	string inputString;
	ifstream myfile("input.txt");
	getline(myfile, inputString);

	
	// remove !x's
	int i = 0;
	while ( i < inputString.length() ) {

		if (inputString[i] == '!') {
			inputString.erase(i, 2);
		}
		else {
			i++;
		}
	}

	

	// erase garbage <...>
	i = 0;
	while (i < inputString.length()) {

		if (inputString[i] == '<') {
			bool endFound = false;
			int j = i + 1;
			while (!endFound) {
				if (inputString[j] == '>') {
					inputString.erase(i, j - i + 1);
					endFound = true;
				}
				else {
					j++;
				}
			}
		}
		else {
			i++;
		}
	}

	cout << inputString << endl;

	cout << "total score is " << Score(1, inputString) << endl;

	cin.get();
	return 0;
}