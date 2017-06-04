/*
ID: kml111
PROG: ratios
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
	ofstream fout("ratios.out");
	ifstream fin("ratios.in");
	int gb, go, gw;
	fin >> gb >> go >> gw;
	//tuple<int, int, int> goal = make_tuple(gb, go, gw);
	vector<tuple<int, int, int>> mixtures(3);
	for (int a = 0; a < 3; ++a) {
		int b, o, w;
		fin >> b >> o >> w;
		mixtures[a] = make_tuple(b, o, w);
	}

	bool found = false;
	long long fact = 1;
	for (int i = 0; i <= 100; ++i) {
		for (int j = 0; j <= 100; ++j) {
			for (int k = 0; k <= 100; ++k) {
				if (!found) {
					if (!(i == 0 && j == 0 && k == 0)) {
						long long currb = (i * get<0>(mixtures[0])) + (j * get<0>(mixtures[1])) + (k * get<0>(mixtures[2]));
						long long curro = (i * get<1>(mixtures[0])) + (j * get<1>(mixtures[1])) + (k * get<1>(mixtures[2]));
						long long currw = (i * get<2>(mixtures[0])) + (j * get<2>(mixtures[1])) + (k * get<2>(mixtures[2]));
						currb *= fact;
						curro *= fact;
						currw *= fact;
						if (gb == 0) {
							if (currb != 0) {
								continue;
							}
							else {
								currb = -1;
							}
						}
						else {
							if (currb % gb != 0) {
								continue;
							}
							currb /= gb;
						}
						if (go == 0) {
							if (curro != 0) {
								continue;
							}
							else {
								curro = -1;
							}
						}
						else {
							if (curro % go != 0) {
								continue;
							}
							curro /= go;
						}
						if (gw == 0) {
							if (currw != 0) {
								continue;
							}
							else {
								currw = -1;
							}
						}
						else {
							if (currw % gw != 0) {
								continue;
							}
							currw /= gw;
						}
						long long maxv = max(max(currb, curro), currw);
						currb = currb == -1 ? maxv : currb;
						curro = curro == -1 ? maxv : curro;
						currw = currw == -1 ? maxv : currw;
						if (currb == curro && curro == currw) { // found the right mixture
							fout << i << " " << j << " " << k << " " << maxv / fact << endl;
							found = true;
							break;
						}
					}
				}
			}
		}
	}

	if (!found) {
		fout << "NONE" << endl;
	}
	return 0;
}