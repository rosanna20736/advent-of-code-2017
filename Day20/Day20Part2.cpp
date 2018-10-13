#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

void readInFile(const string&, vector<vector<int>>&, vector<vector<int>>&, vector<vector<int>>&);
void checkForCollisionsAndDestroyParticles(vector<vector<int>>&, vector<vector<int>>&, vector<vector<int>>&);
void updateParticles(vector<vector<int>>&, vector<vector<int>>&, vector<vector<int>>&);

int main()
{
	string myfilename = "input.txt";
	
	vector<vector<int>> positions(0), velocities(0), accelerations(0);
	readInFile(myfilename, positions, velocities, accelerations);
	
	while (true)
	{
		cout << positions.size() << '\t';
		checkForCollisionsAndDestroyParticles(positions, velocities, accelerations);
		updateParticles(positions, velocities, accelerations);
	}

	cin.get();
	return 0;
}

void readInFile(const string& myfilename, vector<vector<int>>& pos, vector<vector<int>>& vel, vector<vector<int>>& acc)
{
	ifstream myfile(myfilename);
	string line;
	while (getline(myfile, line))
	{
		string pstring, vstring, astring, temp;
		vector<int> p(0), v(0), a(0);
		istringstream iss(line);
		iss >> pstring; iss >> vstring; iss >> astring;

		istringstream piss(pstring.substr(3, pstring.length() - 4));
		while (getline(piss, temp, ','))
		{
			p.push_back(stoi(temp));
		}
		pos.push_back(p);

		istringstream viss(vstring.substr(3, vstring.length() - 4));
		while (getline(viss, temp, ','))
		{
			v.push_back(stoi(temp));
		}
		vel.push_back(v);

		istringstream aiss(astring.substr(3, astring.length() - 4));
		while (getline(aiss, temp, ','))
		{
			a.push_back(stoi(temp));
		}
		acc.push_back(a);
	}
	return;
}

void checkForCollisionsAndDestroyParticles(vector<vector<int>>& positions, vector<vector<int>>& velocities, vector<vector<int>>& accelerations)
{
	for (int i = 0; i < positions.size();)
	{
		bool isADuplicate = false;

		for (int j = positions.size() - 1; j > i; j--)
		{
			if (positions[i] == positions[j])
			{
				isADuplicate = true;
				positions.erase(positions.begin() + j);
				velocities.erase(velocities.begin() + j);
				accelerations.erase(accelerations.begin() + j);
			}
		}
		if (isADuplicate)
		{
			positions.erase(positions.begin() + i);
			velocities.erase(velocities.begin() + i);
			accelerations.erase(accelerations.begin() + i);
		}
		else
		{
			i++;
		}
	}
	return;
}

void updateParticles(vector<vector<int>>& positions, vector<vector<int>>& velocities, vector<vector<int>>& accelerations)
{
	for (int i = 0; i < positions.size(); i++)
	{
		transform(velocities[i].begin(), velocities[i].end(), accelerations[i].begin(), velocities[i].begin(), plus<int>());
		transform(positions[i].begin(), positions[i].end(), velocities[i].begin(), positions[i].begin(), plus<int>());
	}
	return;
}
