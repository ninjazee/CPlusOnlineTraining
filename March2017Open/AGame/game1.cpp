/*
ID: kml111
PROG: game1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

int main() {
	ofstream fout("game1.out");
	ifstream fin("game1.in");
	int n;
	fin >> n;
	vector<int> board(n);
	for (int a = 0; a < n; ++a) {
		int num;
		fin >> num;
		board[a] = num;
	}

	vector<vector<tuple<int, int>>> moves(n, vector<tuple<int, int>>(n)); 

	// do the first move
	vector<tuple<int, int>> firstMove(n);
	for (int b = 0; b < n; ++b) {
		firstMove[b] = make_tuple(board[b], 0);
	}
	moves[0] = firstMove;

	// do the next moves
	for (int i = 1; i < n; ++i) {
		for (int b = 0; b < n - i; ++b) {
			auto scoreA = moves[i - 1][b]; // choosing start from b, length i-1
			auto chooseA = board[b + i];
			int playerA1 = chooseA + get<1>(scoreA);
			int playerA2 = get<0>(scoreA);
			auto scoreB = moves[i - 1][b + 1]; // choosing start from b+1, length i-1
			auto chooseB = board[b];
			int playerB1 = chooseB + get<1>(scoreB);
			int playerB2 = get<0>(scoreB);

			if (playerA1 > playerB1) {
				moves[i][b] = make_tuple(playerA1, playerA2);
			}
			else {
				moves[i][b] = make_tuple(playerB1, playerB2);
			}
		}
	}

	fout << get<0>(moves[n - 1][0]) << ' ' << get<1>(moves[n - 1][0]) << endl;
	return 0;
}