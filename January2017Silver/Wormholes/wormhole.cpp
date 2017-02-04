/*
ID: kml111
PROG: wormhole
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void printMask(vector<int> &mask, const int level) {
	for (int i = 0; i < level; i++)
		cout << "........";
	for (int i = 0; i < (int)mask.size(); i++)
		cout << mask[i] << " ";
	cout << endl; 
}


void pickone(vector<int> &mask, const int level) {
	printMask(mask, level); 
	int n = (int)mask.size();
	if (level < n) {
		for (int i = 0; i < n; ++i) {
			if (mask[i] == 0) {
				mask[i] = level + 1;
				pickone(mask, level + 1);
				mask[i] = 0;
			}
		}
	}
	else
	{
		for (int j = 0; j < n; ++j) {
			cout << mask[j] << ' ';
		}
		cout << endl;
	}
}

int picktwo(vector<int> &mask, const int level, int &count) {
	//printMask(mask, level);
	int n = (int)mask.size();
	if (level < n) {
		int i;
		for (i = 0; i < n; ++i) {
			if (mask[i] == 0) {
				mask[i] = level + 1;
				break;
			}
		}
		for (int j = i + 1; j < n; ++j) {
			if (mask[j] == 0) {
				mask[j] = level + 2;
				picktwo(mask, level + 2, count);
				//printMask(mask, level);
				mask[j] = 0;
			}
		}
		mask[i] = 0;
	}
	else {
		for (int j = 0; j < n; ++j) {
			cout << mask[j] << ' ';
		}
		cout << endl;
		count += 1;

	}
	return count;
}

int main() {
	ofstream fout("wormhole.out");
	ifstream fin("wormhole.in");
	
	int n = 8; 
	vector<int> mask(n, 0);
	int count = 0;

	cout << picktwo(mask, 0, count) << endl; 
	
	return 0;
}