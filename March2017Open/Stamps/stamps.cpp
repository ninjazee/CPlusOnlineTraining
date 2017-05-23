/*
ID: kml111
PROG: stamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MaxValue = 2000001;

int main() {
	ofstream fout("stamps.out");
	ifstream fin("stamps.in");
	int k, n;
	fin >> k >> n;

	vector<int> stamps(n);
	for (int a = 0; a < n; ++a) {
		int s;
		fin >> s;
		stamps[a] = s;
	}

	vector<int> postages(MaxValue, 0); // number of stamps per postage
	for (int b = 0; b < n; ++b) { // put in all of the stamp values
		postages[stamps[b]] = 1;
	}

	
	for (int i = 1; i < MaxValue; ++i) { // for every postage
		int depth = postages[i];
		if (depth != 0 ) {
			if ( depth < k )
			{
				for (int j = 0; j < n; ++j) { // for every stamp
					if (postages[i + stamps[j]] == 0 || postages[i + stamps[j]] > depth + 1) {
						postages[i + stamps[j]] = postages[i] + 1;
					}
				}
			}
		}
		else
		{
			fout << i - 1 << endl;
			return 0; 
		}
	}

	return 0;
}