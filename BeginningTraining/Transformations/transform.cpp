/*
ID: kml111
PROG: ride
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

bool areSame(const vector<string> &before, const vector<string> &after) {
	int n = (int)before.size();
	int i = 0;
	bool same = true;
	while (i < n && same) {
		if (before[i] != after[i]) {
			same = false;
		}
		i += 1;
	}
	return same;
}

void rotate90(const vector<string> &before, vector<string> &output) {

}

void reverseString(const string &input, string &s) {
	int size = input.size();
	for (int i = 0; i < size; ++i) {
		s[size - i - 1] = input[i];
	}
}

void reflectStrings(const vector<string> &before, vector<string> &output) {
	int n = (int)before.size();
	for (int i = 0; i < n; ++i) {
		string s(before[i].size(), '@');
		reverseString(before[i], s);
		output[i] = s;
	}
}

int detectChange(const vector<string> &before, const vector<string> &after) {
	int n = (int)before.size();
	vector<string> output1(n); 
	vector<string> output2(n);
	vector<string> output3(n);
	vector<string> output4(n);
	int retVal = 7;
	
	// check if both vectors are the same (no change, #6)
	if (areSame(before, after)) {
		retVal = 6;
	}

	// check if a reflection occured 
	reflectStrings(before, output4);
	if (areSame(output4, after)) {
		retVal = 4;
	}

	return retVal;
}

int main() {
	ofstream fout("transform.out");
	ifstream fin("transform.in");
	int n;
	fin >> n;
	vector<string> before(n);
	for (int a = 0; a < n; ++a) {
		string line;
		fin >> line;
		before[a] = line;
	}
	vector<string> after(n);
	for (int b = 0; b < n; ++b) {
		string line;
		fin >> line;
		after[b] = line;
	}
	cout << detectChange(before, after) << endl;
	return 0;
}
