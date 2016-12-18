#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

void checkDigits(string num, vector<int> &basenums, int base) {
	for (int c = 0; c < num.length(); ++c) {
		string s = num;
		for (char n = '0'; n < (char)('0'+base); ++n) {
			if (num[c] != n) {
				s[c] = n;
				basenums.push_back(strtol(s.data(), NULL, base));
			}
		}
	}
}

int main() {
	ofstream fout("digits.out");
	ifstream fin("digits1.in");
	string base2, base3;
	fin >> base2;
	fin >> base3;
	vector<int> base2nums;
	vector<int> base3nums;
	checkDigits(base2, base2nums, 2);
	checkDigits(base3, base3nums, 3);
	int n2 = (int)base2nums.size();
	int n3 = (int)base3nums.size();
	unordered_set<int> cache(n2 * 2);
	for (int i = 0; i < n2; ++i) {
		cache.insert(base2nums[i]);
	}
	for (int j = 0; j < n3; ++j) {
		auto pnt = cache.find(base3nums[j]);
		if ( pnt==cache.end() ) {
			// nothing
		}
		else {
			cout << base3nums[j] << endl;
		}
	}
	
	return 0;
}