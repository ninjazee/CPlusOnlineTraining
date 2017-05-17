/*
ID: kml111
PROG: humble
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <bitset>
#include <tuple>
#include <limits>

using namespace std;

typedef bitset<16> Btype;


int main() {
	ofstream fout("humble.out");
	ifstream fin("humble.in");
	int k, n;
	fin >> k >> n;

	vector<int> primes(k);
	set<long long> exam;
	// Push set in
	for (int a = 0; a < k; ++a) {
		int p;
		fin >> p;
		primes[a] = p;
		exam.insert(p);
	}

	int count = 0;
	while (count < n - 1) {
		auto curr = exam.begin();
		long long val = *curr;
		exam.erase(curr);
		//cout << val << endl;
		count += 1;
		long long threshold = numeric_limits<long long>::max(); 
		if (exam.size() > n - count) {
			threshold = *(prev(exam.end()));
		}
		for (int i = 0; i < k; ++i) {
			long long v = val * primes[i];
			if ( v <= threshold)
				exam.insert(v);
		}
		
		if (exam.size() > n - count)
		{
			auto pnt = exam.end(); 
			int nerase = exam.size() - n - count; 
			for (; nerase >= 0; nerase--)
			{
				exam.erase(--pnt);
			}
		}
	}
	auto nPlace = exam.begin();
	long long nHumble = *nPlace;
	fout << nHumble << endl;
	return 0;
}