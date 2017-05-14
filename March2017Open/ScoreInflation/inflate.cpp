/*
ID: kml111
PROG: inflate
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

int main2() {
	ofstream fout("inflate.out");
	ifstream fin("inflate.in");
	int m, n;
	fin >> m >> n;

	vector<tuple<int, int>> classes(n);
	for (int a = 0; a < n; ++a) {
		int points, minutes;
		fin >> points >> minutes;
		classes[a] = make_tuple(points, minutes);
	}
	sort(classes.begin(), classes.end(), TupleCompare<0>());

	vector<vector<int>> combinations(n + 1, vector<int>(m + 1, 0));

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			int numClasses = j / get<1>(classes[i - 1]);
			int newAmount = numClasses * get<0>(classes[i - 1]);
			combinations[i][j] = max(combinations[i - 1][j], newAmount + combinations[i - 1][j - (numClasses * get<1>(classes[i - 1]))]);
		}
	}

	fout << combinations[n][m] << endl;

	return 0;
}

int main() {
	ofstream fout("inflate.out");
	ifstream fin("inflate.in");
	int m, n;
	fin >> m >> n;

	vector<tuple<int, int>> classes(n);
	for (int a = 0; a < n; ++a) {
		int points, minutes;
		fin >> points >> minutes;
		classes[a] = make_tuple(points, minutes);
	}

	vector<int> combinations(m + 1, 0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= m; ++j) {
			if ( j >= get<1>(classes[i]))
			{
				combinations[j] = max(combinations[j], get<0>(classes[i]) + combinations[j - get<1>(classes[i])]);
			}
			//cout << combinations[j] << " ";
		}
		//cout << endl << endl;
	}

	fout << combinations[m] << endl;

	return 0;
}