#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;


void letterCount(string s, vector<int> &letters, vector<int> &whichBoard, vector<string> &whichString, string currstring, int board) {
	for (char c : s) {
		int num = c;
		if (letters[num - 97] != 0 && (whichBoard[num - 97]) % board == 0 && whichString[num-97] != currstring) {
			
		}
		else {
			letters[num - 97] += 1;
			whichBoard[num - 97] += board;
			whichString[num - 97] = currstring;
		}
	}
}


/*
void blockGame(const vector<tuple<string, string>> &boards, vector<int> &letters) {
	int n = (int)boards.size();
	vector<int> whichBoard(26);
	vector<int> whichBoardCheck(26);
	for (int x = 0; x < n; ++x) {
		for (int a = 0; a < 2; ++a) {
			vector<int> letterCheck(26);
			letterCheck.resize(26, x);
			if (a == 0) {
				string s = get<0>(boards[x]);
				for (char c : s) {
					int num = c;
					letters[num - 97] += 1;
					whichBoard[num - 97] = x + 1;
				}
			}
			else {
				string s = get<1>(boards[x]);
				for (char c : s) {
					int num = c;
					letterCheck[num - 97] += 1;
					whichBoardCheck[num - 97] = x + 1;
				}
				for (int b = 0; b < 26; ++b) {
					if (whichBoard[b] == whichBoardCheck[b] && letterCheck[b] >= letters[b]) {
						letters[b] = letterCheck[b];
					}
					else {
						letters[b] += letterCheck[b];
					}
				}
			}
		}
	}
}
*/

void blockGame(const vector<tuple<string, string>> &boards, vector<int> &letters) {
	int n = (int)boards.size();
	vector<int> whichBoard(26);
	vector<string> whichString(26);
	for (int x = 0; x < 2; ++x) {
		for (int a = 0; a < n; ++a) {
			string s;
			if (x == 0) {
				s = get<0>(boards[a]);
				letterCount(s, letters, whichBoard, whichString, get<0>(boards[a]), a + 1);
			}
			else {
				s = get<1>(boards[a]);
				letterCount(s, letters, whichBoard, whichString, get<1>(boards[a]), a + 1);
			}
		}
	}
}


int main() {
	ofstream fout("blocks.out");
	ifstream fin("blocks.in");
	int n;
	fin >> n;
	vector<tuple<string, string>> boards(n);
	for (int i = 0; i < n; ++i) {
		string board1, board2;
		fin >> board1 >> board2;
		auto board = make_tuple(board1, board2);
		boards[i] = board;
	}
	vector<int> letters(26);

	//int numComb = pow(2, n);
	//vector<tuple<string, string, string>> combinations(numComb);

	blockGame(boards, letters);
	for (int x = 0; x < 26; ++x) {
		fout << letters[x] << endl;
	}
	return 0;
}
