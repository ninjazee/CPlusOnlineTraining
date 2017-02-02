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

void pickone(vector<int> &mask, const int level) {
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

void picktwo(vector<int> &mask, const int level) {
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

int main() {
	ofstream fout("wormhole.out");
	ifstream fin("wormhole.in");
	
	int n = 4; 
	vector<int> mask(4, 0);
	pickone(mask, 0); 
	
	return 0;
}