#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool CheckAnagrams(string& str1, string& str2)
{
	sort(str1.begin(), str1.end());
	sort(str2.begin(), str2.end());

	return (str1 == str2);

}


int main() {

	ifstream myfile("input.txt");
	string line;
	int validPhrases = 0;

	while (getline(myfile, line))
	{
		bool isValid = true;
		vector<string> passphrase;

		istringstream iss(line);
		string a;
		while (iss >> a) {
			passphrase.push_back(a);
		}

		for (string str : passphrase) {
			cout << str << '\t';
		}
		cout << endl;

		for (int i = 0; i < passphrase.size(); i++)
		{
			for (int j = 0; j < passphrase.size(); j++)
			{
				if (i != j)
				{
					bool StringsAreAnagrams = CheckAnagrams(passphrase[i], passphrase[j]);
					if (StringsAreAnagrams) {
						isValid = false;
						break;
					}
				}
			}
		}

		if (isValid) {
			validPhrases++;
			cout << "valid" << endl;
		}
		else {
			cout << "not valid" << endl;
		}

	}

	cout << validPhrases;

	cin.get();
	return 0;
}