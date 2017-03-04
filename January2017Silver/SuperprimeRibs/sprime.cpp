/*
ID: kml111
PROG: sprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPrime(const int num) {
	for (int i = 2; i * i <= num; i++) {
		if ((num % i) == 0) {
			return false;
		}
	}
	return true;
}

int numDigits(int number) {
	int digits = 0;
	if (number < 0) digits = 1; // remove this line if '-' counts as a digit
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}


void superprime(const int n, const int level, vector<int> &currnums, vector<int> &superprimes) {
	if (level < n - 1) { // if it is under the digit limit
		for (int i = 0; i < (int)currnums.size(); ++i) { // for each number in the current array
			if (numDigits(currnums[i]) == level + 1) {
				int nums[] = { 1, 3, 7, 9 };
				vector<int> newnums(nums, nums + sizeof(nums) / sizeof(int)); // make a vector of the next digit
				for (int j = 0; j < (int)newnums.size(); ++j) {
					if (isPrime(currnums[i] * 10 + newnums[j])) { // if the numbers are prime
						newnums[j] = currnums[i] * 10 + newnums[j];
					}
				}
				superprime(n, level+1, newnums, superprimes);
			}
		}
	}
	else {
		for (int k = 0; k < (int)currnums.size(); ++k) {
			if (numDigits(currnums[k]) == n) {
				superprimes.push_back(currnums[k]);
			}
		}
	}
}

void superprime1(const int n, const int level, int &currnum, int &orignum, vector<int> &superprimes) {
	if (level < n - 1) { // if it is under the digit limit
		int nums[] = { 1, 3, 7, 9 };
		vector<int> newnums(nums, nums + sizeof(nums) / sizeof(int)); // make a vector of the next digit
		for (int j = 0; j < (int)newnums.size(); ++j) {
			if (isPrime(currnum * 10 + newnums[j])) { // if the numbers are prime
				orignum = currnum;
				currnum = currnum * 10 + newnums[j];
				superprime1(n, level + 1, currnum, orignum, superprimes);
				currnum = orignum;
			}
		}
	}
	else {
		superprimes.push_back(currnum);
	}
}

int main() {
	ofstream fout("sprime.out");
	ifstream fin("sprime.in");
	int n;
	fin >> n;
	int startnums[] = { 2, 3, 5, 7 };
	vector<int> start(startnums, startnums + sizeof(startnums) / sizeof(int));
	vector<int> superprimes;

	int level = 0;
	superprime(n, level, start, superprimes);
	sort(superprimes.begin(), superprimes.end());
	
	for (int a = 0; a < (int)superprimes.size(); ++a) {
		cout << superprimes[a] << endl;
	}
	return 0;
}