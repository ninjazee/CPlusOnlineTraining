/*
ID: kml111
PROG: holstein
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <tuple>

using namespace std;

typedef bitset<16> Btype;


int main() {
	ofstream fout("holstein.out");
	ifstream fin("holstein.in");
	int v;
	fin >> v;
	vector<int> vitamins(v);
	for (int a = 0; a < v; ++a) {
		int vitamin;
		fin >> vitamin;
		vitamins[a] = vitamin;
	}
	int g;
	fin >> g;
	vector<vector<int>> feeds(g, vector<int>(v));
	for (int b = 0; b < g; ++b) {
		for (int c = 0; c < v; ++c) {
			int feedvitamin;
			fin >> feedvitamin;
			feeds[b][c] = feedvitamin;
		}
	}

	queue<tuple<int,int, int,vector<int>>> exam;
	// Push node 0 in 
	exam.push(make_tuple(0,0, -1,vector<int>(v,0)));

	while (!exam.empty()) {
		auto cur_tuple = exam.front();
		exam.pop();
		int cur = get<0>(cur_tuple);
		int size = get<1>(cur_tuple);
		int highest = get<2>(cur_tuple);
		vector<int> &vitamincount = get<3>(cur_tuple);
		bool satisfies = true;
		for (int k = 0; k < v; ++k) {
			if (vitamincount[k] < vitamins[k]) {
				satisfies = false;
				break;
			}
		}
		if (satisfies) {
			fout << size;
			for (int i = 0; i < g; i++) {
				if ((cur & (1 << i)) != 0) {
					fout << ' ' << i + 1;
				}
			}
			fout << endl;
			break;
		}

		// Add a node to queue. 
		for (int i = highest + 1; i < g; ++i) {
			int next = (cur | (1 << i));
			vector<int> nextvitamin(vitamincount);
			for (int j = 0; j < v; j++)
			{
				nextvitamin[j] += feeds[i][j];
			}
			exam.push(make_tuple(next, size+1, i, nextvitamin));
		}
	}

	return 0;
}