/*
ID: kml111
PROG: msquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;


int main() {
	ofstream fout("msquare.out");
	ifstream fin("msquare.in");
	vector<int> target(8);
	for (int a = 0; a < 8; ++a) {
		int integer;
		fin >> integer;
		target[a] = integer;
	}
	
	vector<int> initial(8);
	for (int b = 0; b < 8; ++b) {
		initial[b] = b + 1;
	}

	queue<tuple<vector<int>, string>> exam;
	// Push first node in 
	exam.push(make_tuple(initial, ""));
	auto cur_tuple = exam.front();

	while (!(equal(target.begin(), target.begin() + 8, get<0>(cur_tuple).begin()))) {
		cur_tuple = exam.front();
		exam.pop();

		vector<int> curr = get<0>(cur_tuple);
		string sequence = get<1>(cur_tuple);

		// Add next nodes to queue. 
		// Transformation A
		vector<int> nexta(8);
		for (int i = 0; i < 8; ++i) {
			nexta[i] = curr[-1 * i + 7];
		}
		exam.push(make_tuple(nexta, sequence + 'A'));
		// Transformation B
		vector<int> nextb(8);
		for (int i = 0; i < 8; ++i) {
			if (i == 0) { // switch with 4 place
				nextb[i] = curr[3];
			}
			else if (i >= 1 && i <= 3) { // 2nd to 4th place, use the one behind it
				nextb[i] = curr[i - 1];
			}
			else if (i >= 4 && i <= 6) { // 5th to 7th place, use the one in front of it
				nextb[i] = curr[i + 1];
			}
			else if (i == 7) { // switch with 5th place
				nextb[i] = curr[4];
			}
		}
		exam.push(make_tuple(nextb, sequence + 'B'));
		// Transformation C
		vector<int> nextc(8);
		for (int i = 0; i < 8; ++i) {
			if (i == 1) { // switch with 7 place
				nextc[i] = curr[6];
			}
			else if (i == 2) { // switch with 2 place
				nextc[i] = curr[1];
			}
			else if (i == 5) { // switch with 3 place
				nextc[i] = curr[2];
			}
			else if (i == 6) { // switch with 6 place
				nextc[i] = curr[5];
			}
			else { // normal
				nextc[i] = curr[i];
			}
		}
		exam.push(make_tuple(nextc, sequence + 'C'));
	}
	
	cout << (int)get<1>(cur_tuple).length() << endl << get<1>(cur_tuple) << endl;
	return 0;
}