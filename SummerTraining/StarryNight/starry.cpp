/*
ID: kml111
PROG: starry
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <limits>

using namespace std;

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
	}
};

void printGrid(const vector<string> &grid) {
	int n = (int)grid.size();
	int m = (int)grid[0].size();
	for (int i = 0; i < n; ++i) {
		cout << grid[i];
		cout << endl;
	}
	cout << endl << "-----------------------------------------" << endl;
}

int followGraph(const vector<string> &skyMap, vector<string> &reached, vector<tuple<int, int>> &clusterCoords, const int currentr, const int currentc, const char cluster) {
	if (reached[currentr][currentc] != '.' || skyMap[currentr][currentc] == '0') // if already reached this square it will not lead you anywhere, if there is no star here it will not lead you anywhere
		return 0;
	else {
		int h = (int)skyMap.size();
		int w = (int)skyMap[0].length();
		reached[currentr][currentc] = cluster;
		clusterCoords.push_back(make_tuple(currentr, currentc));
		int count = 1;

		bool isRight = currentc + 1 < w;
		bool isLeft = currentc - 1 >= 0;
		bool isUp = currentr - 1 >= 0;
		bool isDown = currentr + 1 < h;
		
		// deal with N, E, S, and W
		if (isRight && skyMap[currentr][currentc + 1] == '1') { // there is a star to the right; going right: c + 1
			count += followGraph(skyMap, reached, clusterCoords, currentr, currentc + 1, cluster);
		}
		if (isLeft && skyMap[currentr][currentc - 1] == '1') { // There is a star to the left; going left: c - 1
			count += followGraph(skyMap, reached, clusterCoords, currentr, currentc - 1, cluster);
		}
		if (isUp && skyMap[currentr - 1][currentc] == '1') { // there is a star above; going up: r + 1
			count += followGraph(skyMap, reached, clusterCoords, currentr - 1, currentc, cluster);
		}
		if (isDown && skyMap[currentr + 1][currentc] == '1') { // there is a star underneath; going down: r - 1
			count += followGraph(skyMap, reached, clusterCoords, currentr + 1, currentc, cluster);
		}

		// deal with NE, NW, SE, and SW
		if (isUp && isRight && skyMap[currentr - 1][currentc + 1] == '1') { // there is a star to the above right; going up and right: r + 1, c + 1
			count += followGraph(skyMap, reached, clusterCoords, currentr - 1, currentc + 1, cluster);
		}
		if (isUp && isLeft && skyMap[currentr - 1][currentc - 1] == '1') { // There is a star to the above left; going up and left: r + 1, c - 1
			count += followGraph(skyMap, reached, clusterCoords, currentr - 1, currentc - 1, cluster);
		}
		if (isDown && isRight && skyMap[currentr + 1][currentc + 1] == '1') { // there is a star underneath right; going down and right: r - 1, c + 1
			count += followGraph(skyMap, reached, clusterCoords, currentr + 1, currentc + 1, cluster);
		}
		if (isDown && isLeft && skyMap[currentr + 1][currentc - 1] == '1') { // there is a star underneath left; going down and left: r - 1, c - 1
			count += followGraph(skyMap, reached, clusterCoords, currentr + 1, currentc - 1, cluster);
		}

		return count;
	}
}

int main() {
	ofstream fout("starry.out");
	ifstream fin("starry.in");
	int w, h;
	fin >> w >> h;
	vector<string> skyMap(h);
	for (int a = 0; a < h; ++a) {
		string row;
		fin >> row;
		skyMap[a] = row;
	}

	vector<string> reached(h, string(w, '.'));
	vector<int> clusterSize;
	vector<vector<tuple<int, int>>> clusterCoords;
	int clusterNumber = 0;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			vector<tuple<int, int>> coords;
			int cSize = followGraph(skyMap, reached, coords, i, j, 'a' + clusterNumber);
			if (cSize > 0) {
				clusterSize.push_back(cSize);
				clusterCoords.push_back(coords);
				clusterNumber += 1;
			}
		}
	}

	printGrid(reached);

	vector<vector<string>> clusters(clusterNumber);
	for (int a = 0; a < clusterNumber; ++a) {
		int left = numeric_limits<int>::max();
		int right = 0;
		int up = numeric_limits<int>::max();
		int down = 0;
		for (int b = 0; b < (int)clusterCoords[a].size(); ++b) {
			int r = get<0>(clusterCoords[a][b]);
			int c = get<1>(clusterCoords[a][b]);
			if (c > right) {
				right = c;
			}
			if (c < left) {
				left = c;
			}
			if (r > down) {
				down = r;
			}
			if (r < up) {
				up = r;
			}
		}
		vector<string> cluster(down - up + 1);
		for (int c = up; c <= down; ++c) {
			for (int d = left; d <= right; ++d) {
				if (reached[c][d] == 'a' + a) { // this is a part of the cluster
					cluster[c - up].push_back('1');
				}
				else {
					cluster[c - up].push_back('0');
				}
			}
		}
		clusters[a] = cluster;
	}

	for (int i = 0; i < clusterNumber; ++i) {
		for (int j = i + 1; j < clusterNumber; ++j) {
			if (clusterSize[i] == clusterSize[j]) { // these might be the same
				for (int x = 0; x < 8; ++x) {
					for (int y = 0; y < 8; ++y) {

					}
				}
			}
		}
	}

	return 0;
}