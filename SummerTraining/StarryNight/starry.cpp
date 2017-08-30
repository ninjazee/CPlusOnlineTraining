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
#include <unordered_set>

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
	if (reached[currentr][currentc] != '0' || skyMap[currentr][currentc] == '0') // if already reached this square it will not lead you anywhere, if there is no star here it will not lead you anywhere
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

int followGraph2(const vector<string> &skyMap, vector<vector<int>> &reached, vector<tuple<int, int>> &clusterCoords, const int currentr, const int currentc, const int cluster) {
	if (reached[currentr][currentc] != -1 || skyMap[currentr][currentc] == '0') // if already reached this square it will not lead you anywhere, if there is no star here it will not lead you anywhere
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
			count += followGraph2(skyMap, reached, clusterCoords, currentr, currentc + 1, cluster);
		}
		if (isLeft && skyMap[currentr][currentc - 1] == '1') { // There is a star to the left; going left: c - 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr, currentc - 1, cluster);
		}
		if (isUp && skyMap[currentr - 1][currentc] == '1') { // there is a star above; going up: r + 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr - 1, currentc, cluster);
		}
		if (isDown && skyMap[currentr + 1][currentc] == '1') { // there is a star underneath; going down: r - 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr + 1, currentc, cluster);
		}

		// deal with NE, NW, SE, and SW
		if (isUp && isRight && skyMap[currentr - 1][currentc + 1] == '1') { // there is a star to the above right; going up and right: r + 1, c + 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr - 1, currentc + 1, cluster);
		}
		if (isUp && isLeft && skyMap[currentr - 1][currentc - 1] == '1') { // There is a star to the above left; going up and left: r + 1, c - 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr - 1, currentc - 1, cluster);
		}
		if (isDown && isRight && skyMap[currentr + 1][currentc + 1] == '1') { // there is a star underneath right; going down and right: r - 1, c + 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr + 1, currentc + 1, cluster);
		}
		if (isDown && isLeft && skyMap[currentr + 1][currentc - 1] == '1') { // there is a star underneath left; going down and left: r - 1, c - 1
			count += followGraph2(skyMap, reached, clusterCoords, currentr + 1, currentc - 1, cluster);
		}

		return count;
	}
}

bool areSame(const vector<string> &before, const vector<string> &after) {
	int n = (int)before.size();
	int n2 = (int)after.size();
	if (n != n2) {
		return false;
	}
	int i = 0;
	bool same = true;
	while (i < n && same) {
		if (before[i] != after[i]) {
			same = false;
		}
		i += 1;
	}
	return same;
}

void rotate90(const vector<string> &before, vector<string> &output) {
	int n = (int)before.size();
	int m = (int)before[0].size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			string beforeString = before[i];
			char beforeChar = beforeString[j];
			output[j][n - 1 - i] = beforeChar;
		}
	}
}

void reverseString(const string &input, string &s) {
	int size = (int)input.size();
	for (int i = 0; i < size; ++i) {
		s[size - i - 1] = input[i];
	}
}

void reflectStrings(const vector<string> &before, vector<string> &output) {
	int n = (int)before.size();
	for (int i = 0; i < n; ++i) {
		string s((int)before[i].size(), '@');
		reverseString(before[i], s);
		output[i] = s;
	}
}

bool areSimilar(const vector<string> &before, const vector<string> &after) {
	int n = (int)before.size();
	int m = (int)before[0].size();
	vector<string> output1(m, string(n, ' '));
	vector<string> output2(n, string(m, ' '));
	vector<string> output3(m, string(n, ' '));
	vector<string> output4(n, string(n, ' '));
	vector<string> output5(m, string(n, ' '));
	vector<string> output6(n, string(m, ' '));
	vector<string> output7(m, string(n, ' '));

	// check if a 90 degree rotation occurred
	rotate90(before, output1);
	if (areSame(output1, after)) {
		return true;
	}

	// check if a 180 degree rotation occurred
	rotate90(output1, output2);
	if (areSame(output2, after)) {
		return true;
	}

	//check if a 270 degree rotation occurred
	rotate90(output2, output3);
	if (areSame(output3, after)) {
		return true;
	}

	// check if a reflection occured 
	reflectStrings(before, output4);
	if (areSame(output4, after)) {
		return true;
	}

	//check if a 90 degree rotation and a reflection occured
	rotate90(output4, output5);
	if (areSame(output5, after)) {
		return true;
	}

	// check if a 180 degree rotation and a reflection occured
	rotate90(output5, output6);
	if (areSame(output6, after)) {
		return true;
	}

	// check if a 270 degree rotation and a reflection occured
	rotate90(output6, output7);
	if (areSame(output7, after)) {
		return true;
	}

	// check if both vectors are the same (no change, #6)
	if (areSame(before, after)) {
		return true;
	}


	return false;
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

	vector<vector<int>> reached(h, vector<int>(w, -1));
	vector<int> clusterSize;
	vector<vector<tuple<int, int>>> clusterCoords;
	vector<int> clusterLetters;
	int clusterNumber = 0;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			vector<tuple<int, int>> coords;
			int cSize = followGraph2(skyMap, reached, coords, i, j, clusterNumber);
			if (cSize > 0) {
				clusterSize.push_back(cSize);
				clusterCoords.push_back(coords);
				clusterLetters.push_back(clusterNumber);
				clusterNumber += 1;
			}
		}
	}

	//printGrid(reached);

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
				if (reached[c][d] == a) { // this is a part of the cluster
					cluster[c - up].push_back(skyMap[c][d]);
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
				if (clusterLetters[i] != clusterLetters[j] && areSimilar(clusters[i], clusters[j])) { // these two clusters are similar and we haven't already seen this one
					int counter = 0;
					int jChar = clusterLetters[j];
					//vector<bool> seen(clusterNumber, false);
					for (int k = j; k < clusterNumber; ++k) {
						if (k == j) { // this is the j cluster
							clusterLetters[k] = clusterLetters[i];
						}
						else if (clusterLetters[k] > jChar) { // this is a cluster after the j cluster
							clusterLetters[k] = jChar + counter;
							counter += 1;
						}
					}
				}
			}
		}
	}

	vector<string> output(h, string(w, '0'));
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			if (reached[i][j] != -1) { // there is a cluster here
				// give the cluster its correct assigned letter
				output[i][j] = clusterLetters[reached[i][j]] + 'a';
			}
		}
	}

	for (int i = 0; i < h; ++i) {
		fout << output[i] << endl;
	}
	return 0;
}

/*
int extraAdd = 0;
unordered_set<char> seen;
char jChar = clusterLetters[j];
for (int a = 0; a < h; ++a) {
	for (int b = 0; b < w; ++b) {
		if (reached[a][b] == clusterLetters[j]) { // this is part of the j cluster
												  // change it to i
			reached[a][b] = clusterLetters[i];
		}
		else if ((reached[a][b] - 'a') >(clusterLetters[j] - 'a')) { // this is a cluster after the j cluster
																	 // shift it back
			int difference = (reached[a][b] - 'a') - (clusterLetters[j] - 'a');
			reached[a][b] = (char)((int)clusterLetters[j] + difference + extraAdd - 1);
		}
		else if (reached[a][b] != '0' && (int)reached[a][b] < (int)clusterLetters[j]) { // this is a cluster before the j cluster
			if (seen.find(reached[a][b]) == seen.end()) { // we haven't already seen this cluster
				extraAdd += 1;
			}
		}
	}
}
clusterLetters[j] = clusterLetters[i];
printGrid(reached);
*/