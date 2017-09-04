/*
ID: kml111
PROG: ride
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int convert(string comet) {
	int retValue = 1;
	for (char& c : comet) {
		int diff = c - 'A' + 1;
		retValue *= diff;
	}
	return retValue;
}

int main() {
	ofstream fout("ride.out");
	ifstream fin("ride.in");
	string a, b;
	fin >> a >> b;
	int aValue = convert(a);
	int bValue = convert(b);
	if (aValue % 47 == bValue % 47) {
		fout << "GO" << endl;
	}
	else {
		fout << "STAY" << endl;
	}
	return 0;
}