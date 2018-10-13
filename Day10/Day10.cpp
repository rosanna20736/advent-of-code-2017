#include <iostream>
#include <vector>
#include <sstream>
#include <ios>
using namespace std;



int main() {

	// initialise lengths
	string inputString = "225,171,131,2,35,5,0,13,1,246,54,97,255,98,254,110";
	//string inputString = "1,2,4";
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

			//for (int i = 0; i < listSize; i++) {
			//	if (i == currentPos) {
			//		cout << "(" << theList[i] << ")" << '\t';
			//	}
			//	else {
			//		cout << theList[i] << '\t';
			//	}
			//}
			//cout << endl;

		}

	}

	// sparse hash -> desnse hash
	vector<int> denseHash(16);
	for (int i = 0; i < 16; i++) {
		//vector<int> subList(16);
		//copy(theList.begin() + i*16, theList.begin() + (i+1) * 16, subList.begin());
		int hashElem = theList[i * 16];
		for (int j = i * 16 + 1; j < (i+1) * 16; j++) {
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
	

	cout << ss.str() << endl;

	cin.get();
	return 0;
}