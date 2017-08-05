/*
ID: kml111
PROG: frameup
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <limits>

using namespace std;

void findOrder(const vector<unordered_set<int>> &onTopList, const vector<int> &numArrows, vector<char> &order, const int node) {
	int leastArrowNum = numeric_limits<int>::max();
	int leastArrowNode;
	order.push_back(char(node + 'A'));
	for (auto curr : onTopList[node]) { // for everything the start node is on top of
		if (numArrows[curr] < leastArrowNum) { // this has the least arrows
			leastArrowNum = numArrows[curr];
			leastArrowNode = curr;
		}
	}
	if (leastArrowNum < numeric_limits<int>::max()) { // we haven't reached the end node
		findOrder(onTopList, numArrows, order, leastArrowNode);
	}
}

int main() {
	ofstream fout("frameup.out");
	ifstream fin("frameup.in");
	int h, w;
	fin >> h >> w;
	vector<string> frameArray(h);
	int numFrames = 0;
	unordered_set<char> frames;
	for (int a = 0; a < h; ++a) {
		string row;
		fin >> row;
		frameArray[a] = row;
		for (int b = 0; b < w; ++b) {
			if (row[b] != '.') {
				if (frames.find(row[b]) == frames.end()) { // we haven't already seen this frame
					frames.insert(row[b]);
					numFrames += 1;
				}
			}
		}
	}

	// find the boundaries of the frames
	vector<vector<int>> boundaries(numFrames, vector<int>(4, -1));
	for (int i = 0; i < h; ++i) { // for every row
		for (int j = 0; j < w; ++j) { // for every column
			if (frameArray[i][j] != '.') { // if it is a letter
				int letter = frameArray[i][j] - 'A';
				if (boundaries[letter][0] == -1) { // we haven't ever seen this frame
					// assume that this is the top right
					boundaries[letter][0] = i;
					boundaries[letter][1] = j;
				}
				else { // we have seen this frame
					if (boundaries[letter][2] == -1) { // we haven't seen the other boundary of this frame
						// assume that this is the boundary
						boundaries[letter][2] = i;
						boundaries[letter][3] = j;
					}
					else { // we have seen both boundaries before
						if (i < boundaries[letter][0]) { // this is more up than we thought the boundaries were
							// make it the new boundary
							boundaries[letter][0] = i;
						}
						if (i > boundaries[letter][2]) { // this is more down than we thought the boundaries were
							// make it the new boundary
							boundaries[letter][2] = i;
						}
						if (j < boundaries[letter][1]) { // this is more left than we thought the boundaries were
							// make it the new boundary
							boundaries[letter][1] = j;
						}
						if (j > boundaries[letter][3]) { // this is more left than we thought the boundaries were
							// make it the new boundary
							boundaries[letter][3] = j;
						}
					}
				}
			}
		}
	}

	vector<unordered_set<int>> onTopList(numFrames, unordered_set<int>());
	for (int i = 0; i < numFrames; ++i) {
		char letter = i + 'A';
		for (int r = boundaries[i][0]; r <= boundaries[i][2]; ++r) {
			if (r == boundaries[i][0] || r == boundaries[i][2]) { // it's one of the top sides
				for (int c = boundaries[i][1]; c <= boundaries[i][3]; ++c) {
					if (frameArray[r][c] != letter) { // something is covering this frame up
						int newLetter = frameArray[r][c] - 'A';
						if (onTopList[newLetter].find(i) == onTopList[newLetter].end()) {
							onTopList[newLetter].insert(i);
						}
					}
				}
			}
			else { // it's not a top side
				if (frameArray[r][boundaries[i][1]] != letter) { // something is covering this frame up
					int newLetter = frameArray[r][boundaries[i][1]] - 'A';
					if (onTopList[newLetter].find(i) == onTopList[newLetter].end()) {
						onTopList[newLetter].insert(i);
					}
				}
				if (frameArray[r][boundaries[i][3]] != letter) { // something is covering this frame up
					int newLetter = frameArray[r][boundaries[i][3]] - 'A';
					if (onTopList[newLetter].find(i) == onTopList[newLetter].end()) {
						onTopList[newLetter].insert(i);
					}
				}
			}
		}
	}

	// find the number of arrows pointing to each frame
	vector<int> numArrows(numFrames);
	for (int i = 0; i < numFrames; ++i) {
		for (auto it : onTopList[i]) {
			numArrows[it] += 1;
		}
	}

	// find the order of the frames
	vector<char> order;
	int start;
	for (int i = 0; i < numFrames; ++i) { // find the start node
		if (numArrows[i] == 0) { // we found the one on top
			start = i;
			break;
		}
	}
	findOrder(onTopList, numArrows, order, start);

	// print
	for (int i = (int)order.size() - 1; i >= 0; --i) {
		cout << order[i];
	}
	cout << endl;
	return 0;
}