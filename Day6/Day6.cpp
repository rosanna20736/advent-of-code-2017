#include <iostream>
#include <algorithm>
using namespace std;

bool isEqual(int * a, int * b, int len) 
{
	for (int i = 0; i < len; i++) {
		if (a[i] != b[i]) {
			return false;
		}

	}
	return true;
}

int main() {

	int myInput[] = {5,1,10,0,1,7,13,14,3,12,8,10,7,12,0,6};
	const int inputLength = 16;
	//int myInput[] = { 0,2,7,0 };
	//const int inputLength = 4;
	const int maxIters = 10000;
	int configs[maxIters*inputLength];
	int redistCycles = 0;
	bool repeatDetected = false;

	for (int i = 0; i < inputLength; i++) {
		configs[i] = myInput[i];
	}

	while (!repeatDetected && redistCycles < maxIters) {
		redistCycles++;
		int * currentConfig = configs + redistCycles*inputLength;
		for (int i = 0; i < inputLength; i++) {
			configs[redistCycles*inputLength + i] = configs[(redistCycles - 1)*inputLength + i];
		}
		int * pmaxPos = max_element(currentConfig, currentConfig + inputLength);
		int maxPos = distance(currentConfig, pmaxPos);

		int toRedistribute = *pmaxPos;

		*pmaxPos = 0;
		for (int i = 1; i <= toRedistribute; i++)
		{
			currentConfig[(maxPos + i) % inputLength] ++;
		}

		//for (int i = 0; i < inputLength; i++)
		//{
		//	cout << currentConfig[i] << '\t';
		//}
		//cout << '\n';

		for (int i = 0; i < redistCycles; i++)
		{
			if (isEqual(currentConfig, configs + i*inputLength, inputLength))
			{
				cout << "loop length: " << redistCycles - i << endl;
				repeatDetected = true;
				break;
			}
		}

		
	}

	if (repeatDetected) {
		cout << "Repeat found after " << redistCycles << " cycles.";
	}
	else {
		cout << "max iters reached";
	}

	cin.get();

	return 0;
}