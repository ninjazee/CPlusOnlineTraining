/*
ID: kml111
PROG: buylow
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_set>

using namespace std;

int main() {
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");
	int n;
	fin >> n;
	vector<long long> prices(n);
	for (int a = 0; a < n; ++a) {
		long long price;
		fin >> price;
		prices[a] = price;
	}

	vector<tuple<int, long long>> totals(n); // number of times you buy, number of combinations
	for (int i = n - 1; i >= 0; --i) { // for every sequence of numbers from day i on
		int numTimes = 0;
		long long numComb = 0;
		unordered_set<int> seen; // unordered set of day numbers
		for (int j = i + 1; j < n; ++j) { // for every number after i
			if (prices[i] > prices[j]) { // if we can buy on this day (the price on this day is less than the price today)
				if (get<0>(totals[j]) > numTimes) { // if the number of times we can buy on this day is larger than our current best
					if (seen.find(prices[j]) == seen.end()) { // if we have not already seen this value
						numTimes = get<0>(totals[j]);
						numComb = get<1>(totals[j]);
						seen.insert(prices[j]);
					}
				}
				else if (get<0>(totals[j]) == numTimes) { // if the number of times we can buy on this day is equal to our current best
					if (seen.find(prices[j]) == seen.end()) { // if we have not already seen this value
						numComb += get<1>(totals[j]);
						seen.insert(prices[j]);
					}
				}
			}
		}
		get<0>(totals[i]) = numTimes + 1; // the total for this day is our best from the days before plus one more for today
		if (numComb == 0) { // if we didn't find any days that worked
			get<1>(totals[i]) = 1; // there is one for today
		}
		else { // we found some days that worked, use that number
			get<1>(totals[i]) = numComb;
		}
	}

	int bestTimes = 0;
	long long bestComb = 0;
	for (int x = 0; x < n; ++x) { // for every tuple in our totals vector
		if (get<0>(totals[x]) > bestTimes) { // a new largest number of days
			bestTimes = get<0>(totals[x]);
			bestComb = get<1>(totals[x]);
		}
		else if (get<0>(totals[x]) == bestTimes) { // more combinations
			bestComb += get<1>(totals[x]);
		}
	}
	fout << bestTimes << ' ' << bestComb << endl;
	return 0;
}