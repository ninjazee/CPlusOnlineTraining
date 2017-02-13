#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

int countcross(const vector<tuple<tuple<int, int>, tuple<int, int>>> &roads, const vector<tuple<int, int>> &cows) {
	int k = (int)cows.size();
	int r = (int)roads.size();

	int distpairs = 0;
	for (int x = 0; x < k; ++x) {
		for (int z = 0; z < k - 1; ++z) {
			int y = (x + z + 1) % 3;
			for (int i = 0; i < r; ++i) {
				if (get<0>(cows[x]) <= get<0>(get<0>(roads[i])) && get<0>(cows[x]) >= get<1>(get<0>(roads[i]))) {
					if (get<0>(cows[y]) <= get<0>(get<0>(roads[i])) && get<0>(cows[y]) >= get<1>(get<0>(roads[i]))) {
						if (get<1>(cows[x]) <= get<0>(get<1>(roads[i])) && get<1>(cows[x]) >= get<1>(get<1>(roads[i]))) {
							if (get<1>(cows[y]) <= get<0>(get<1>(roads[i])) && get<1>(cows[y]) >= get<1>(get<1>(roads[i]))) {
								distpairs += 1;
								break;
							}
						}
					}
				}
			}
		}
	}

	return distpairs;
}

int main() {
	ofstream fout("countcross.out");
	ifstream fin("countcross.in");
	int n, k, r;
	fin >> n >> k >> r;
	
	vector<tuple<tuple<int, int>, tuple<int, int>>> roads(r);
	for (int a = 0; a < r; ++a) {
		int r, c, r1, c1;
		fin >> r >> c >> r1 >> c1;
		roads[a] = make_tuple(make_tuple(r, c), make_tuple(r1, c1));
	}

	vector <tuple<int, int>> cows(k);
	for (int b = 0; b < k; ++b) {
		int r, c;
		fin >> r >> c;
		cows[b] = make_tuple(r, c);
	}

	fout << countcross(roads, cows) << endl;
	return 0;
}
