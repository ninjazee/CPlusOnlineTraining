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
#include <algorithm>
#include <string>

using namespace std;

class BigNum {
private:
	vector<int> digits;
public:
	BigNum() { assign(0); }
	BigNum(const int val) { assign(val); }
	BigNum(BigNum const &bn);

	void assign(const int n);
	void add(const BigNum &second);
	string ToString();
};

BigNum::BigNum(BigNum const &bn) {
	for (int i = 0; i < (int)bn.digits.size(); ++i) {
		digits.push_back(bn.digits[i]);
	}
}

void BigNum::assign(const int n) {
	int temp = n; // a storage
	while (temp > 0) {
		digits.push_back(temp % 10); // push this digit into digits
		temp /= 10;
	}
}

void BigNum::add(const BigNum &second) {
	int carry = 0;
	int sizeA = (int)digits.size(); // the number of digits in our current number
	int sizeB = (int)second.digits.size(); // the number of digits in the second number
	for (int i = sizeA; i < sizeB; i++)
	{
		digits.push_back(0);
	}
	int i = 0;
	for (; i < sizeB; ++i) {
		digits[i] = digits[i] + second.digits[i] + carry; // add the two digits
		// deal with amount carried on
		carry = digits[i] / 10; 
		digits[i] %= 10; 
	}
	for (; i < sizeA; ++i)
	{
		digits[i] = digits[i] + carry; // add the two digits
		// deal with amount carried on
		carry = digits[i] / 10;
		digits[i] %= 10;

	}
	if (carry != 0) {
		digits.push_back(carry);
	}
	
}

string BigNum::ToString() {
	string retstr;
	for (int i = (int)digits.size() - 1; i >= 0; --i) {
		retstr.push_back(digits[i] + '0');
	}
	return retstr;
}

int main() {
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");
	int n;
	fin >> n;
	vector<int> prices(n);
	for (int a = 0; a < n; ++a) {
		int price;
		fin >> price;
		prices[a] = price;
	}

	vector<tuple<int, BigNum>> totals(n); // number of times you buy, number of combinations
	for (int i = 0; i < n; ++i) { // for every sequence of numbers from day i back
		int numTimes = 0;
		BigNum numComb(1);
		unordered_set<int> seen;
		for (int j = i-1; j >=0; --j) { // for every number after i
			if (prices[i] < prices[j]) { // if we can buy on this day (the price on this day is more than the price today)
				if (get<0>(totals[j]) > numTimes) { // if the number of times we can buy on this day is larger than our current best
					numTimes = get<0>(totals[j]);
					numComb = get<1>(totals[j]);
					seen.clear();
					seen.insert(prices[j]);
				}
				else if (get<0>(totals[j]) == numTimes) { // if the number of times we can buy on this day is equal to our current best
					if (seen.find(prices[j]) == seen.end()) { // we haven't already seen the same number;
						numComb.add(get<1>(totals[j]));
						seen.insert(prices[j]);
					}
				}
			}
		}
		get<0>(totals[i]) = numTimes + 1; // the total for this day is our best from the days before plus one more for today
		get<1>(totals[i]) = numComb;
	}

	int bestTimes = 0;
	BigNum bestComb(0);
	unordered_set<int> seen;
	for (int x = n - 1; x >= 0; --x) { // for every tuple in our totals vector (starting from the back to take care of duplicates
		if (get<0>(totals[x]) > bestTimes) { // a new largest number of days
			bestTimes = get<0>(totals[x]);
			bestComb = get<1>(totals[x]);
			seen.clear();
			seen.insert(prices[x]);
		}
		else if (get<0>(totals[x]) == bestTimes) { // more combinations
			if (seen.find(prices[x]) == seen.end()) {
				bestComb.add(get<1>(totals[x]));
			}
		}
	}
	string bComb = bestComb.ToString();
	fout << bestTimes << " " << bComb << endl;
	return 0;
}