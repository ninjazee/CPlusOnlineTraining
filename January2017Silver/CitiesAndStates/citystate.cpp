#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

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
	ofstream fout("citystate.out");
	ifstream fin("citystate.in");
	int n;
	fin >> n;

	unordered_map<string, int> citystate;
	unordered_map<string, int> statecity;
	for (int a = 0; a < n; ++a) {
		string c, s;
		fin >> c >> s;
		string cs; // create string that is first two letters of city and state combined
		string sc; // create string that is state and first two letters of city
		if (c.substr(0, 2) != s) {
			cs = c.substr(0, 2) + s;
			sc = s + c.substr(0, 2);
			auto got = citystate.find(cs);
			if (got == citystate.end()) // not found
				citystate[cs] = 1;
			else
				citystate[cs] += 1;

			auto got1 = statecity.find(sc);
			if (got1 == statecity.end()) // not found
				statecity[sc] = 1;
			else
				statecity[sc] += 1;
		}
	}

	int tally = 0;
	for (auto b : citystate) {
		auto got = statecity.find(b.first);
		if (got != statecity.end()) // not found
				tally += b.second * got->second;
	}

	fout << tally / 2<< endl;
	return 0;
}