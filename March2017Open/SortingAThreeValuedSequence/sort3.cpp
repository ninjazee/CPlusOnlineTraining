/*
ID: kml111
PROG: sort3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	int n;
	fin >> n;
	vector<int> nums(n);
	for (int a = 0; a < n; ++a) {
		int num;
		fin >> num;
		nums[a] = num;
	}

	vector<int> sortednums(nums); // create sorted version of list of numbers
	sort(sortednums.begin(), sortednums.end());

	vector<vector<int>> exchanges(3, vector<int>(3, 0)); // create vector<vector<int>> of exchanges needed to be made

	for (int b = 0; b < n; ++b) {
		exchanges[nums[b] - 1][sortednums[b] - 1] += 1; // mark as an exchange needed to be made
	}
	
	int numexchange = 0;
	// check if any switches can immediately be made
	if (exchanges[1][0] != 0 && exchanges[0][1] != 0) {
		int minof = min(exchanges[0][1], exchanges[1][0]);
		numexchange += minof; // add minimum of numbers
	}
	if (exchanges[2][1] != 0 && exchanges[1][2] != 0) {
		int minof = min(exchanges[2][1], exchanges[1][2]);
		numexchange += minof;
	}
	if (exchanges[2][0] != 0 && exchanges[0][2] != 0) {
		int minof = min(exchanges[2][0], exchanges[0][2]);
		numexchange += minof;
	}

	// find remaining number of exchanges
	int exchange12 = max(exchanges[0][1], exchanges[1][0]) - min(exchanges[0][1], exchanges[1][0]); // all exchanges are the same so you only need to find one

	numexchange += exchange12 * 2;

	fout << numexchange << endl;
	return 0;
}