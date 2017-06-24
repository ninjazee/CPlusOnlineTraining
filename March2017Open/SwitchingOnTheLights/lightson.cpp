#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_set>

using namespace std;

int code(const int r, const int c) {
	return r * 100 + c;
}

void decode(const int code, int &r, int &c)
{
	r = code / 100; 
	c = code % 100;
}

int main() {
	ofstream fout("lightson.out");
	ifstream fin("lightson.in");
	int n, m;
	fin >> n >> m;
	vector<vector<int>> switches(10000, vector<int>());
	for (int i = 0; i < m; ++i) {
		int x, y, a, b;
		fin >> x >> y >> a >> b;
		switches[code(x - 1, y - 1)].push_back(code(a - 1, b - 1));
	}
	vector<vector<bool>> grid(n, vector<bool>(n, false));
	grid[0][0] = true;

	vector<vector<bool>> been(n, vector<bool>(n, false));

	queue<tuple<int, int>> exam;
	// Push node 0 in 
	exam.push(make_tuple(0, 0));

	unordered_set<int> reachable;

	while (!exam.empty()) {
		auto cur_tuple = exam.front();
		exam.pop();
		int r = get<0>(cur_tuple);
		int c = get<1>(cur_tuple);
		been[r][c] = true;
		// turn on any switches here.
		auto currentSwitch = switches[code(r, c)];
		for (int i = 0; i < (int)currentSwitch.size(); ++i) {
			int currentCode = currentSwitch[i];
			int switchr, switchc;
			decode(currentCode, switchr, switchc);
			grid[switchr][switchc] = true;
		}

		// Add a node to queue. 
		if (r + 1 < n && been[r + 1][c] == false) { // we can go up
			reachable.insert(code(r + 1, c));
		}
		if (r - 1 >= 0 && been[r - 1][c] == false) { // we can go down
			reachable.insert(code(r - 1, c));
		}
		if (c + 1 < n && been[r][c + 1] == false) { // we can go right
			reachable.insert(code(r, c + 1));
		}
		if (c - 1 >= 0 && been[r][c - 1] == false) { // we can go left
			reachable.insert(code(r, c - 1));
		}

		vector<int> remove;
		// check to see if we can go to any rooms
		for (auto t = reachable.begin(); t != reachable.end(); ++t) { // for every value in reachable
			int nextint = *t;
			int nextr;
			int nextc;
			decode(nextint, nextr, nextc);
			if (grid[nextr][nextc] && been[nextr][nextc] == false) { // the light is on and we haven't been here
				// add it to the queue
				exam.push(make_tuple(nextr, nextc));
				remove.push_back(nextint);
			}
		}

		for (int i = 0; i < (int)remove.size(); ++i) {
			reachable.erase(remove[i]);
		}
	}

	int count = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == true) {
				count += 1;
			}
		}
	}
	fout << count << endl;
	return 0;
}