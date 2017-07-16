/*
ID: kml111
PROG: stall4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_set>

using namespace std;

int main() {
	ofstream fout("stall4.out");
	ifstream fin("stall4.in");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> cowStalls(n);
	vector<vector<int>> stallCows(m);
	for (int a = 0; a < n; ++a) {
		int s;
		fin >> s;
		for (int b = 0; b < s; ++b) {
			int stall;
			fin >> stall;
			cowStalls[a].push_back(stall);
			stallCows[stall - 1].push_back(a);
		}
	}

	queue<tuple<int, unordered_set<int>>> exam;
	for (int x = 0; x < cowStalls[0].size(); ++x) {
		unordered_set<int> currLine;
		currLine.insert(cowStalls[0][x]);
		exam.push(make_tuple(0, currLine));
	}

	int best = 0;
	while (!exam.empty()) {
		auto curr = exam.front();
		exam.pop();
		int currCow = get<0>(curr);
		unordered_set<int> currStalls = get<1>(curr);
		int stallAmount = (int)currStalls.size();
		if (stallAmount > best) { // check if we have a larger number of stalls
			best = stallAmount;
		}

		if (currCow < n - 1) { // we have not used all of the cows
			for (int i = 0; i < cowStalls[currCow + 1].size(); ++i) { // for every of the next cow's possible stalls
				if (currStalls.find(cowStalls[currCow + 1][i]) == currStalls.end()) { // if we did not already use this stall
					unordered_set<int> newStalls(currStalls);
					newStalls.insert(cowStalls[currCow + 1][i]);
					exam.push(make_tuple(currCow + 1, newStalls));
				}
			}
		}
	}

	cout << best << endl;
	return 0;
}