/*
ID: kml111
PROG: gift1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	ofstream fout("gift1.out");
	ifstream fin("gift1.in");
	int np;
	fin >> np;
	vector<string> names(np);
	for (int i = 0; i < np; ++i) {
		string name; 
		fin >> name;
		names[i] = name;
	}
	map<string, int> accounts;
	map<string, int> gave;
	map<string, int> recieved;

	for (int i = 0; i < np; ++i) {
		string n;
		fin >> n;
		int money;
		int ng;
		fin >> money >> ng;
		if (ng != 0) {
			int mdivide = money / ng;
			gave[n] = mdivide * ng;
			for (int j = 0; j < ng; ++j) {
				string giveN;
				fin >> giveN;
				recieved[giveN] += mdivide;
			}
		}
		else {
			gave[n] = 0;

		}
	}
	for (int k = 0; k < np; ++k) {
		string nm = names[k];
		accounts[nm] = recieved[nm] - gave[nm];
		fout << nm << " " << accounts[nm] << endl;
	}
	return 0;
}
