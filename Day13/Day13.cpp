#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class Layer {
	int range;
public:
	int depth;
	Layer(int d, int r) : depth(d), range(r) {}
	bool operator < (const Layer b) { return depth < b.depth; };
	bool operator == (int i) { return depth == i; };
	bool hitScanner(int);
	int layerSeverity() { return depth * range; };
};

vector<Layer> importFile(string);
int computeSeverity(vector<Layer>&);
int numberOfPicosecondsToDelay(vector<Layer>&);
bool youGetCaught(int, vector<Layer>&);

int main()
{
	string myfilename = "input.txt";
	vector<Layer> firewallLayers = importFile(myfilename);
	int severity = computeSeverity(firewallLayers);
	cout << "total severity = " << severity << endl;
	int picosecondsToDelay = numberOfPicosecondsToDelay(firewallLayers);
	cout << "picoseconds to delay = " << picosecondsToDelay << endl;

	cin.get();
	return 0;
}


bool Layer::hitScanner(int delay)
{
	return ((delay + depth) % (2 * (range-1))) == 0;
}

vector<Layer> importFile(string myfilename)
{
	vector<Layer> layers;
	ifstream myfile(myfilename);
	string line;
	while (getline(myfile, line))
	{
		istringstream iss(line);
		string depthColon, rangeStr;
		iss >> depthColon;
		iss >> rangeStr;
		Layer thisLayer(stoi(depthColon.substr(0, depthColon.length() - 1)), stoi(rangeStr));
		layers.push_back(thisLayer);
	}
	return layers;
}

int computeSeverity(vector<Layer>& firewallLayers)
{
	int myDepth = 0;
	int severity = 0;
	int maxDepth = (max_element(firewallLayers.begin(), firewallLayers.end()))->depth;

	for (int myDepth = 0; myDepth <= maxDepth; myDepth++)
	{
		vector<Layer>::iterator itToThisLayer = find(firewallLayers.begin(), firewallLayers.end(), myDepth);
		if (itToThisLayer != firewallLayers.end())
		{
			if (itToThisLayer->hitScanner(0))
			{
				severity += itToThisLayer->layerSeverity();
			}
		}

	}

	return severity;
}

bool youGetCaught(int delay, vector<Layer>& firewallLayers)
{
	int myDepth = 0;
	int maxDepth = (max_element(firewallLayers.begin(), firewallLayers.end()))->depth;

	for (int myDepth = 0; myDepth <= maxDepth; myDepth++)
	{
		vector<Layer>::iterator itToThisLayer = find(firewallLayers.begin(), firewallLayers.end(), myDepth);
		if (itToThisLayer != firewallLayers.end())
		{
			if (itToThisLayer->hitScanner(delay))
			{
				return true;
			}
		}

	}

	return false;
}

int numberOfPicosecondsToDelay(vector<Layer>& firewallLayers)
{
	bool delayFound = false;
	int currentDelay = 0;
	int winningDelay;
	do
	{
		if (!youGetCaught(currentDelay, firewallLayers))
		{
			winningDelay = currentDelay;
			delayFound = true;
		}
		currentDelay++;

	} while (!delayFound);

	return winningDelay;
}
