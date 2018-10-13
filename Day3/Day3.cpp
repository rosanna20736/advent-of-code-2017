#include <iostream>
using namespace std;


int main() {

	int myNum = 325489;
	//int myNum = 19;

	int largestSquare = 1;
	while (largestSquare*largestSquare < myNum) {
		largestSquare += 2;
	}
	largestSquare -= 2;

	int startPos = largestSquare / 2;
	int overflow = myNum - largestSquare*largestSquare;

	int side = overflow / (largestSquare + 1);
	int overflow2 = overflow % (largestSquare + 1);



	return 0;
}