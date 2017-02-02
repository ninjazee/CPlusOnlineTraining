/*
ID: kml111
PROG: beads
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void createArray(string beads, vector<char> &necklace) {
	int i = 0;
	for (char c : beads) {
		necklace[i] = c;
		i += 1;
	}
	for (char c : beads) {
		necklace[i] = c;
		i += 1;
	}
}

int brokenNecklace(int n, const vector<char> &necklace) {
	int best = 0;
	for (int b = 0; b < n; ++b) {
		// count how many beads there are going forward
		int countf = 1;
		char beadf = necklace[b];
		while (beadf == 'w') {
			beadf = necklace[b + countf];
			countf += 1;
		}
		bool runningf = true;
		while (runningf) {
			if (countf > n) {
				//countf -= 1;
				runningf = false;
			}
			else if (necklace[b + countf] == 'w' || necklace[b + countf] == beadf) {
				countf += 1;
			}
			else {
				runningf = false;
			}
		}

		// count how many beads there are going backward
		int countb = 1;
		int a = b + n - 1;
		char beadb = necklace[a];
		while (beadb == 'w') {
			beadb = necklace[a - countb];
			countb += 1;
		}
		bool runningb = true;
		while (runningb) {
			if (countb > n) {
				//countb -= 1;
				runningb = false;
			}
			else if (a - countb < 0) {
				runningb = false;
			}
			else if (necklace[a - countb] == 'w' || necklace[a - countb] == beadb) {
				countb += 1;
			}
			else {
				runningb = false;
			}
		}

		// count how many beads there are total
		int numbeads = countf + countb;
		if (numbeads > n) {
			numbeads = n;
		}
		if (numbeads > best) {
			best = numbeads;
		}
	}
	return best;
}

int main() {
	ofstream fout("beads.out");
	ifstream fin("beads.in");
	int n;
	fin >> n;
	string beads;
	fin >> beads;
	vector<char> necklace(n * 2);
	createArray(beads, necklace);
	fout << brokenNecklace(n, necklace) << endl;
	return 0;
}
