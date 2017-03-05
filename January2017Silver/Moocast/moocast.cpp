#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

void calculateDist(const vector<tuple<int, int, int>> &cows, vector<vector<int>> &edge) {
	int n = (int)cows.size();
	
	for (int i = 0; i < n; ++i) { // for each cow
		int powerSq = get<2>(cows[i]) * get<2>(cows[i]);
		for (int j = 0; j < n; ++j) { // check how far from every other cow
			if (i != j) {
				// calculate distance between cow i and cow j
				int dx = (get<0>(cows[i]) - get<0>(cows[j]));
				int dy = (get<1>(cows[i]) - get<1>(cows[j]));
				int dist = (dx * dx) + (dy * dy);

				// if the distance <= power, add it to the list of cows it can reach.
				if (dist <= powerSq) {
					edge[i].push_back(j);
				}
			}
		}
	}
}

int followGraph(const vector<vector<int>> &edge, vector<bool> &reached, const int current) {
	if (reached[current])
		return 0; 
	else {
		reached[current] = true;
		int count = 1; 
		for (int i : edge[current]) { // for each value that the current node connects to
			count += followGraph(edge, reached, i);
		}
		return count; 
	}
}

int main() {
	ofstream fout("moocast.out");
	ifstream fin("moocast.in");
	int n;
	fin >> n;
	vector<tuple<int, int, int>> cows(n);
	for (int a = 0; a < n; ++a) {
		int x, y, p;
		fin >> x >> y >> p;
		cows[a] = make_tuple(x, y, p);
	}
	vector<vector<int>> edge(n, vector<int>());
	
	calculateDist(cows, edge);

	int best = 0;
	for (int b = 0; b < n; ++b) {
		vector<bool> reached(n, false);
		int count = followGraph(edge, reached, b);
		
		if (count > best) {
			best = count;
		}
	}

	fout << best << endl;
 	return 0;
}