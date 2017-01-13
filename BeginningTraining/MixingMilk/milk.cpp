/*
ID: kml111
PROG: milk
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
	}
};

int mixingMilk(const int n, vector<tuple<int, int>> &farmers) {
	sort(farmers.begin(), farmers.end(), TupleCompare<0>());
	int counter = 0;
	int placehold = 0;
	int cost = 0;
	while (counter < n) {
		if (n - counter - get<1>(farmers[placehold]) < 0) {
			cost += get<0>(farmers[placehold]) * (n - counter);
			counter += (n - counter);
		}
		else {
			cost += get<0>(farmers[placehold]) * get<1>(farmers[placehold]);
			counter += get<1>(farmers[placehold]);
		}
		placehold += 1;
	}
	return cost;
}

int main() {
	ofstream fout("milk.out");
	ifstream fin("milk.in");
	int n, m;
	fin >> n >> m;
	vector<tuple<int, int>> farmers;
	for (int x = 0; x < m; ++x) {
		int p, a;
		fin >> p >> a;
		farmers.push_back(tuple<int, int>(p, a));
	}
	fout << mixingMilk(n, farmers) << endl;
	return 0;
}