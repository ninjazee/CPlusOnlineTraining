#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int hayBales(int n, vector<int> &bales) {
	sort(bales.begin(), bales.end());
	int time = 1;
	int highest = 0;
	for (int i = 0; i < n; ++i) {
		int time = 1;
		int counter = 0;
		
		if (bales[i] + time == bales[i + time]) {
			while (bales[i] + time == bales[i + time]) {
				counter += 1;
				time += 1;
			}
		}

		else if (bales[i] - time == bales[i - time]) {
			while (bales[i] - time == bales[i - time]) {
				counter += 1;
				time += 1;
			}
		}

		if (counter > highest) {
			highest = counter;
		}
	}
	return highest;
}

int main() {
	ofstream fout("angry.out");
	ifstream fin("angry.in");
	int n;
	fin >> n;
	vector<int> bales(n);
	for (int b = 0; b < n; ++b) {
		int h;
		fin >> h;
		bales[b] = h;
	}
	cout << hayBales(n, bales) << endl;
	return 0;
}