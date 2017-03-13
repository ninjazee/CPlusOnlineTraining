#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

/*
template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2, T const &t3)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2, std::get<M>(t3)));
	}
};
*/

int bovineGenomics(const int m, const vector<string> &scows, const vector<string> &pcows) {
	int n = (int)scows.size();
	int total = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = i; j < m; ++j) {
			if (i != j) {
				for (int k = j; k < m; ++k) {
					if (k != i && k != j) {
						bool isGenome = true;
						vector<tuple<char, char, char>> sset(n);
						for (int x = 0; x < n; ++x) {
							sset[x] = make_tuple(scows[x][i], scows[x][j], scows[x][k]);
						}
						vector<tuple<char, char, char>> pset((int)pcows.size());
						for (int y = 0; y < n; ++y) {
							pset[y] = make_tuple(pcows[y][i], pcows[y][j], pcows[y][k]);
						}

						//sort(sset.begin(), sset.end(), TupleCompare<0>());
						//sort(pset.begin(), pset.end(), TupleCompare<0>());

						for (int a = 0; a < n; ++a) {
							for (int b = 0; b < n; ++b) {
								if (sset[a] == pset[b]) {
									isGenome = false;
								}
							}
						}

						if (isGenome == true) {
							total += 1;
						}
					}
				}
			}
		}
	}
	return total;
}

int main() {
	ofstream fout("cownomics.out");
	ifstream fin("cownomics.in");
	int n, m;
	fin >> n >> m;
	
	vector<string> scows(n);
	vector<string> pcows(n);
	for (int a = 0; a < n; ++a) {
		string sc;
		fin >> sc;
		scows[a] = sc;
	}
	for (int b = 0; b < n; ++b) {
		string pc;
		fin >> pc;
		pcows[b] = pc;
	}

	fout << bovineGenomics(m, scows, pcows) << endl;
	return 0;
}