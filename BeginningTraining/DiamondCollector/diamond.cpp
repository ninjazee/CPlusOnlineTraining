#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int diamondDisplay(vector<int> A, int n, int k) {
	sort(A.begin(), A.end());
	int most = 0;
	for (int i = 0; i < n-1; ++i) {
		int j = i+1;
		int currNum = A[i] + k;
		while (j < n && A[j] <= currNum) {
			j += 1;
		}
		if (j - i > most) {
			most = j - i;
		}
	}
	return most;
}

int main() {
	ofstream fout("diamond.out");
	ifstream fin("diamond.in");
	int n, k;
	fin >> n >> k;
	vector<int> diamonds(n);
	for (int a = 0; a < n; ++a) {
		int d;
		fin >> d;
		diamonds[a] = d;
	}
	fout << diamondDisplay(diamonds, n, k) << endl;
	return 0;
}