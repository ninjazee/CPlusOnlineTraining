/*
ID: kml111
PROG: hamming
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int power(const int a, const int b) { // returns a^b
	if (b == 0) {
		return 1;
	}
	else {
		int retval = a;
		for (int i = 0; i < b; ++i) {
			retval *= a;
		}
		return retval;
	}
}

int main() {
	ofstream fout("hamming.out");
	ifstream fin("hamming.in");
	int n, b, d;
	fin >> n >> b >> d;
	
	vector<int> codewords;
	codewords.push_back(0); // add 0 to start
	for (int a = 1; a < power(2, b); ++a) { // for every number with the number of bits b
		if ((int)codewords.size() >= n) { // if we already have n codewords
			break;
		}
		else {
			// check to see if this codeword has the correct hamming distance from all of the other codes
			bool isCodeWord = true;
			for (int i = 0; i < (int)codewords.size(); ++i) { // for every code
				int different = 0; // number of bits that are different
				for (int j = 0; j < b; ++j) { // for each bit
					if (((a >> j) & 1) != ((codewords[i] >> j) & 1)) { // if the bit is different
						different += 1;
					}
				}
				if (different < d) { // if the hamming distance is less than d
					isCodeWord = false;
					break;
				}
			}
			
			if (isCodeWord == true) { // if the hamming distance works
				codewords.push_back(a);
			}
		}
	}

	int numPerLine = 1;
	fout << codewords[0];
	for (int c = 1; c < (int)codewords.size(); ++c) {
		if (numPerLine == 10) {
			fout << endl;
			numPerLine = 0;
			fout << codewords[c];
		}
		else {
			fout << ' ' << codewords[c];
		}
		numPerLine += 1;
	}
	fout << endl;
	return 0;
}