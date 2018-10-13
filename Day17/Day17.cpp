#include <iostream>
#include <vector>
using namespace std;

constexpr int STEPS_PER_INSERT = 386;
constexpr int NUMBER_OF_INSERTS = 50000000;

int main()
{
	vector<int> circularBuffer(1);
	int currentBufferSize = 1;
	int currentPosition = 0;
	circularBuffer[0] = 0;
	for (int i = 1; i <= NUMBER_OF_INSERTS; i++)
	{
		currentPosition = (currentPosition + STEPS_PER_INSERT) % currentBufferSize;
		if (currentPosition == 0)
		{
			circularBuffer.insert(circularBuffer.begin() + currentPosition + 1, i);
		}
		currentBufferSize++;
		currentPosition++;
	}
	for (int i = 0;i < 10;i++)
	{
		cout << circularBuffer[i] << '\t';
	}
	cin.get();
	return 0;
}