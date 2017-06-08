#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

void printGrid(const vector<vector<int>> &reached) {
	int n = (int)reached.size();
	for (int y = 0; y < n; ++y) { // for each row
		for (int z = 0; z < n; ++z) { // for each column
			cout << reached[y][z] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int followGraph(const vector<string> &grid, vector<vector<int>> &reached, const int rb1, const int rb2, const int cb1, const int cb2, const int currentr, const int currentc, const int cont) {
	if (reached[currentr][currentc] != -1) // if already reached this square it will not lead you anywhere
		return 0;
	else {
		reached[currentr][currentc] = cont;
		char currchar = grid[currentr][currentc];
		int count = 1;

		if (currentc + 1 <= cb2 && grid[currentr][currentc + 1] == currchar) { // there is not a wall to the right; going right: c + 1
			count += followGraph(grid, reached, rb1, rb2, cb1, cb2, currentr, currentc + 1, cont);
		}
		if (currentc - 1 >= cb1 && grid[currentr][currentc - 1] == currchar) { // there is not a wall to the left; going left: c - 1
			count += followGraph(grid, reached, rb1, rb2, cb1, cb2, currentr, currentc - 1, cont);
		}
		if (currentr + 1 <= rb2 && grid[currentr + 1][currentc] == currchar) { // there is not a wall above; going up: r + 1
			count += followGraph(grid, reached, rb1, rb2, cb1, cb2, currentr + 1, currentc, cont);
		}
		if (currentr - 1 >= rb1 && grid[currentr - 1][currentc] == currchar) { // there is not a wall underneath; going down: r - 1
			count += followGraph(grid, reached, rb1, rb2, cb1, cb2, currentr - 1, currentc, cont);
		}

		return count; 
	}
}

bool isPCL(const vector<string> &grid, const int rb1, const int rb2, const int cb1, const int cb2) {
	int n = (int)grid.size();
	
	vector<vector<int>> reached(n, vector<int>(n, -1));
	// figure out how big the rooms are and how many rooms there are
	unordered_map<char, int> hist;
	int cont = 0;
	for (int x = rb1; x <= rb2; ++x) { // for each row
		for (int y = cb1; y <= cb2; ++y) { // for each square
			char curc = grid[x][y];
			int val = reached[x][y];
			int contSize = followGraph(grid, reached, rb1, rb2, cb1, cb2, x, y, cont);
			if (val==-1) { // there is a room
				auto it = hist.find(curc);
				if (it == hist.end()) {
					hist[curc] = 1;
				}
				else {
					hist[curc] += 1;
				}
				cont += 1;
			}
		}
	}

	//printGrid(reached);
	
	int hs = (int)hist.size();
	if (hs != 2) { // there is not exacly two colors, it is not a PCL
		return false;
	}
	else { // there is exactly two colors
		bool contiguous1 = false;
		bool contiguous2 = false;
		auto pnt = hist.begin();
		int cnt1 = pnt->second;
		pnt++;
		int cnt2 = pnt->second;
		if (cnt1 == 1 && cnt2 >= 2) {
			return true;
		}
		else if (cnt2 == 1 && cnt1 >= 2) {
			return true;
		}
		else {
			return false;
		}
	}
}

int main() {
	ofstream fout("where.out");
	ifstream fin("where.in");
	int n;
	fin >> n;
	vector<string> grid(n);
	for (int a = 0; a < n; ++a) {
		string row;
		fin >> row;
		grid[a] = row;
	}

	int count = 0;
	vector<tuple<int, int, int, int>> pastPCL; 
	for (int rb1 = 0; rb1 < n; ++rb1) {
		for (int cb1 = 0; cb1 < n; ++cb1) {
			bool bFound = false; 
			for (int rb2 = n - 1; rb2 >= rb1; --rb2) {
				for (int cb2 = n - 1; cb2 >= cb1; --cb2) {
					if (isPCL(grid, rb1, rb2, cb1, cb2)) {
						// bFound = true;
						pastPCL.push_back(make_tuple(rb1, rb2, cb1, cb2));
						//cout << rb1 << " " << rb2 << " " << cb1 << " " << cb2 << endl;
						// break; 
					}
				}
				if (bFound) {
					break;
				}
			}
		}
	}
	int sz = (int)pastPCL.size();
	cout << "PCLs == " << sz << endl; 

	for (int i = 0; i < (int)pastPCL.size(); i++)
	{
		bool isInside = false;
		int rb1 = get<0>(pastPCL[i]);
		int rb2 = get<1>(pastPCL[i]);
		int cb1 = get<2>(pastPCL[i]);
		int cb2 = get<3>(pastPCL[i]);

		for (int j = 0; j < (int)pastPCL.size(); j++) {
			if ( i!=j)
			{
				int prb1 = get<0>(pastPCL[j]);
				int prb2 = get<1>(pastPCL[j]);
				int pcb1 = get<2>(pastPCL[j]);
				int pcb2 = get<3>(pastPCL[j]);
				if (rb1 >= prb1 && rb2 <= prb2 && cb1 >= pcb1 && cb2 <= pcb2) {
					isInside = true;
					cout << "Eliminate: " << rb1 << " " << rb2 << " " << cb1 << " " << cb2 <<
						" in " << prb1 << " " << prb2 << " " << pcb1 << " " << pcb2 << endl;
					break;
				}
			}
		}
		if (!isInside)
		{
			count++;
			cout << rb1 << " " << rb2 << " " << cb1 << " " << cb2 << endl;
		}
		else
		{
			
		}
	}

	cout << count << endl;
	return 0;
}