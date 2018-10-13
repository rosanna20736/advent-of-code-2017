#include<iostream>
#include<cmath>
using namespace std;


bool isComposite(int);

int main()
{
	int cnt=0;
	for (int b = 106700; b <= 123700; b += 17)
	{
		if (isComposite(b))
		{
			cnt++;
		}
	}

	cout << cnt << endl;

	cin.get();
	return 0;
}

bool isComposite(int b)
{
	int n = sqrt(b);
	bool composite = false;
	for (int i = 2; i <= n; i++)
	{
		if (b % i == 0)
		{
			composite = true;
			break;
		}
	}

	return composite;
}


