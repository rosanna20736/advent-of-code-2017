#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

enum class stateName
{
	A, B, C, D, E, F
};

enum class moveInstruction
{
	left, right
};

class state
{
	bool zeroWrite, oneWrite;
	moveInstruction zeroMove, oneMove;
	stateName zeroContinueState, oneContinueState;

public:
	state(bool zW, moveInstruction zMI, stateName zCS, bool oW, moveInstruction oMI, stateName oCS) :
		zeroWrite(zW), zeroMove(zMI), zeroContinueState(zCS), oneWrite(oW), oneMove(oMI), oneContinueState(oCS) {}

	stateName actInstructionsAndGiveNextState(map<int, bool>&, int&);
};

int main()
{
	map<int, bool> slots;
	int currentPosition = 0;
	stateName currentState = stateName::A;
	int numSteps = 12399302;
	// test input
	 //state stateA(true, moveInstruction::right, stateName::B, false, moveInstruction::left, stateName::B);
	 //state stateB(true, moveInstruction::left, stateName::A, true, moveInstruction::right, stateName::A);
	// my input
	state stateA(true, moveInstruction::right, stateName::B, false, moveInstruction::right, stateName::C);
	state stateB(false, moveInstruction::left, stateName::A, false, moveInstruction::right, stateName::D);
	state stateC(true, moveInstruction::right, stateName::D, true, moveInstruction::right, stateName::A);
	state stateD(true, moveInstruction::left, stateName::E, false, moveInstruction::left, stateName::D);
	state stateE(true, moveInstruction::right, stateName::F, true, moveInstruction::left, stateName::B);
	state stateF(true, moveInstruction::right, stateName::A, true, moveInstruction::right, stateName::E);

	for (int i = 0; i < numSteps; i++)
	{
		switch (currentState)
		{
		case stateName::A:
			currentState = stateA.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		case stateName::B:
			currentState = stateB.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		case stateName::C:
			currentState = stateC.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		case stateName::D:
			currentState = stateD.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		case stateName::E:
			currentState = stateE.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		case stateName::F:
			currentState = stateF.actInstructionsAndGiveNextState(slots, currentPosition);
			break;
		}
		if ((i % (numSteps / 100)) == 0)
		{
			cout << (i * 100) / numSteps << endl;
		}
	}

	int checkSum = count_if(slots.begin(), slots.end(), [](pair<int, bool> p) {return p.second;});

	cout << "checkSum = " << checkSum << endl;

	cin.get();
	return 0;
}

stateName state::actInstructionsAndGiveNextState(map<int, bool>& slots, int& currentPosition)
{
	bool isZero = !slots[currentPosition];
	if (isZero)
	{
		slots[currentPosition] = zeroWrite;
		if (zeroMove == moveInstruction::left) { currentPosition--; }
		else { currentPosition++; }
		return zeroContinueState;
	}
	else
	{
		slots[currentPosition] = oneWrite;
		if (oneMove == moveInstruction::left) { currentPosition--; }
		else { currentPosition++; }
		return oneContinueState;
	}
}
