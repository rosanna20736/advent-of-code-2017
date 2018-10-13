#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {

	//string inputString = "{<{oli!a,<{i<a>}";
	string inputString;
	ifstream myfile("input.txt");
	getline(myfile, inputString);

	int nestingLevel = 1;
	int score = 0;
	bool inGarbage = false;
	int garbageCount = 0;

	for (int i = 0; i < inputString.length(); i++) {
		char c = inputString[i];
		
		if (inGarbage) {
			if (c == '!') {
				i++;
			} else if (c == '>') {
				inGarbage = false;
			}
			else {
				garbageCount++;
			}
		}
		else {
			if (c == '{') {
				score += nestingLevel++;
			}
			else if (c == '}') {
				nestingLevel--;
			} else if (c == '<') {
				inGarbage = true;
			}
		}
	}

	cout << "total score is " << score << endl;
	cout << "garbage count is " << garbageCount << endl;

	cin.get();
	return 0;
}