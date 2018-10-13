#include <iostream>
#include <vector>
using namespace std;

int main() {
	const int max_Iters = 10;
	vector<int> configs[max_Iters];

	//vector<int> myInput = {5,1,10,0,1,7,13,14,3,12,8,10,7,12,0,6};
	vector<int> myInput = { 0,2,7,0 };
	const int inputLength = myInput.size();
	configs[0] = myInput;

	for (int i = 0; i < inputLength; i++)
	{
		cout << configs[0][i] << '\t';
	}
	cout << '\n';

	bool repeatFound = false;
	int redistCycles = 0;

	while (!repeatFound)
	{



	}

	cin.get();
	return 0;
}