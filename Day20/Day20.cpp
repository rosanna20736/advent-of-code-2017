#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;


int main()
{
	ifstream myfile("input.txt");
	vector<int> manhattanAccelerations(0);
	string line;
	while (getline(myfile, line))
	{
		string temp, astring;
		istringstream iss(line);
		iss >> temp; iss >> temp;
		iss >> astring;

		istringstream aiss(astring.substr(3, astring.length() - 4));
		int manhattanAcceleration = 0;
		while (getline(aiss, temp, ','))
		{
			manhattanAcceleration += abs(stoi(temp));
		}
		manhattanAccelerations.push_back(manhattanAcceleration);
	}

	int min_pos = distance(manhattanAccelerations.begin(), min_element(manhattanAccelerations.begin(), manhattanAccelerations.end()));
	
	cout << min_pos;

	cin.get();
	return 0;
}