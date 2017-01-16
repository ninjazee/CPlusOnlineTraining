#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

bool calculateWin(int a, int b, int h, int p, int s) {
	if (a == h) {
		if (b == p) {
			return false;
		}
		else if (b == s) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (a == p) {
		if (b == h) {
			return true;
		}
		else if (b == s) {
			return false;
		}
		else {
			return false;
		}
	}
	else {
		if (b == h) {
			return false;
		}
		else if (b == p) {
			return true;
		}
		else {
			return false;
		}
	}
}

void threenums(const int h, const int y, int &p, int &s) {
	if (y == 0) {
		if (h == 2) {
			p = 0;
			s = 1;
		}
		else {
			p = h + 1;
			if (p == 1) {
				s = 2;
			}
			else {
				s = p - 2;
			}
		}
	}
	else {
		if (h == 0) {
			p = 2;
			s = 1;
		}
		else {
			p = h - 1;
			if (p == 1) {
				s = 0;
			}
			if (p == 0) {
				s = 2;
			}
		}
	}
}

int hps(vector<tuple<int, int>> games) {
	int mostWins = 0;
	for (int h = 0; h < 3; ++h) {
		for (int y = 0; y < 2; ++y) {
			int p, s;
			threenums(h, y, p, s);

			int wins = 0;
			for (int z = 0; z < (int)games.size(); ++z) {
				if (calculateWin((get<0>(games[z]) - 1), (get<1>(games[z]) - 1), h, p, s) == true) {
					wins += 1;
				}
			}

			if (wins > mostWins) {
				mostWins = wins;
			}
		}
	}
	return mostWins;
}

int main() {
	ofstream fout("hps.out");
	ifstream fin("hps.in");
	int n;
	fin >> n;
	vector<tuple<int, int>> games(n);
	for (int x = 0; x < n; ++x) {
		int a, b;
		fin >> a >> b;
		games[x] = make_tuple(a, b);
	}
	fout << hps(games) << endl;
	return 0;
}