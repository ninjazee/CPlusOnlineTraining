#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void cowsignal(int k, const vector<string> &signal, vector<string> &enlargedSignal) {
	int m = (int)signal.size();
	int n = (int)signal[0].length();
	for (int a = 0; a < m; ++a) {
		string eline;
		for (int b = 0; b < n; ++b) {
			char ch = signal[a][b];
			for (int c = 0; c < k; ++c) {
				eline.push_back(ch);
			}
		}
		for (int d = 0; d < k; ++d) {
			enlargedSignal.push_back(eline);
		}
	}
}

int main() {
	ofstream fout("cowsignal.out");
	ifstream fin("cowsignal.in");
	int m, n, k;
	fin >> m >> n >> k;
	vector<string> signal(m);
	for (int i = 0; i < m; ++i) {
		string line;
		fin >> line;
		signal[i] = line;
	}
	vector<string> enlargedSignal;
	cowsignal(k, signal, enlargedSignal);
	for (int x = 0; x < k * m; ++x) {
		fout << enlargedSignal[x] << endl;
	}
	return 0;
}
