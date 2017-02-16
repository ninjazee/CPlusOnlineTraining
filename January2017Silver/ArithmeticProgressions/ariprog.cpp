/*
ID: kml111
PROG: ariprog
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

void arithmeticProgressions(const int n, const int m, const vector<char> &bisquares, vector<tuple<int, int>> &ariprogs) {
	for (int a = 0; a < m * m + m * m; ++a) { // go through all possible values of a
		if (bisquares[a] == 1) { // check if a is a bisquare
			for (int b = 1; b <= (m * m + m * m - a) / (n - 1); ++b) { // go through all possible values of b
				bool isariprog = true;
				for (int c = n - 1; c > 0; --c) { // check each number in the sequence
					if (/*a + c * b > m * m + m * m || */bisquares[a + c * b] != 1) {
						isariprog = false;
						break;
					}
				}
				if (isariprog) {
					ariprogs.push_back(make_tuple(a, b));
				}
				
				/*
				if (a + n * b < m * m + m * m && bisquares[a + n * b] == 1) {
					ariprogs.push_back(make_tuple(a, b));
				}
				*/
			}
		}
	}
}

int main() {
	ofstream fout("ariprog.out");
	ifstream fin("ariprog.in");
	int n, m;
	fin >> n;
	fin >> m;
	
	vector<char> bisquares((m * m) + (m * m) + 1);
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= m; ++j) {
			int bisquare = i * i + j * j;
			bisquares[bisquare] = 1;
		}
	}

	vector<tuple<int, int>> ariprogs;

	arithmeticProgressions(n, m, bisquares, ariprogs);
	sort(ariprogs.begin(), ariprogs.end(), TupleCompare<1>());

	if ((int)ariprogs.size() < 1) {
		fout << "NONE" << endl;
	}
	else {
		for (int x = 0; x < (int)ariprogs.size(); ++x) {
			fout << get<0>(ariprogs[x]) << ' ' << get<1>(ariprogs[x]) << endl;
		}
	}
	
	return 0;
}