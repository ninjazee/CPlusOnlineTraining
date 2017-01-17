#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool calculateWin(const char a, const char b) {
	if (a =='H') {
		if (b =='P') {
			return false;
		}
		else if (b =='S') {
			return true;
		}
		else {
			return false;
		}
	}
	else if (a =='P') {
		if (b =='H') {
			return true;
		}
		else if (b =='S') {
			return false;
		}
		else {
			return false;
		}
	}
	else {
		if (b =='H') {
			return false;
		}
		else if (b =='P') {
			return true;
		}
		else {
			return false;
		}
	}
}

char whichGesture(const char b) {
	char a;
	if (b == 'P') {
		a = 'S';
	}
	else if (b == 'S') {
		a = 'H';
	}
	else {
		a = 'P';
	}
	return a;
}

int hps(vector<char> fgestures) {
	int n = (int)fgestures.size();
	int best = 0;
	for (int i = 0; i < n; ++i) {
		int wins = 0;
		char cgesture = whichGesture(fgestures[0]);
		for (int j = 0; j < n; ++j) {
			if (j < i) {
				if (calculateWin(cgesture, fgestures[j]) == true) {
					wins += 1;
				}
			}
			else {
				if (j == i) {
					cgesture = whichGesture(fgestures[j]);
				}
				if (calculateWin(cgesture, fgestures[j]) == true) {
					wins += 1;
				}
			}
		}

		if (wins > best) {
			best = wins;
		}
	}
	return best;
}

int main() {
	ofstream fout("hps.out");
	ifstream fin("hps.in");
	int n;
	fin >> n;
	vector<char> fgestures(n);
	for (int x = 0; x < n; ++x) {
		char gesture;
		fin >> gesture;
		fgestures[x] = gesture;
	}
	fout << hps(fgestures) << endl;
	return 0;
}