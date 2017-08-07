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
#include <algorithm>

using namespace std;

void findCombinations(const vector<int> v, const int curr, vector<bool> &picked, const int comb, vector<vector<int>> &combinations) {
	int vSize = (int)v.size();
	picked[curr] = true;
	combinations[comb].push_back(v[curr]);
	vector<int> cComb(combinations[comb]);
	int tally = 0;
	for (int i = 0; i < vSize; ++i) {
		if (!picked[i]) { // if we haven't already picked this one
			if (tally > 0) {
				combinations.push_back(cComb);
			}
			findCombinations(v, i, picked, comb + tally, combinations);
			tally += 1;
		}
	}
	picked[curr] = false;
}

void findOrder(const vector<unordered_set<int>> &onTopList, const vector<int> &numArrows, const vector<vector<int>> &arrowNums, vector<string> &order, vector<vector<bool>> &seen, const vector<bool> &exists, const int combNum, int &numOfCombs, const int node) {
	int leastArrowNum = numeric_limits<int>::max();
	vector<int> leastArrowNode;
	order[combNum].push_back(char(node + 'A'));
	string currentComb(order[combNum]);
	seen[combNum][node] = true;
	vector<bool> newSeenVect(seen[combNum]);
	for (auto curr : onTopList[node]) { // for everything the start node is on top of
		if (numArrows[curr] < leastArrowNum) { // this has the least arrows
			leastArrowNum = numArrows[curr];
			leastArrowNode.clear();
			leastArrowNode.push_back(curr);
		}
		else if (numArrows[curr] == leastArrowNum) {
			leastArrowNode.push_back(curr);
		}
	}

	int otherArrowNum = (int)arrowNums[numArrows[node]].size();
	vector<int> sameLevels;
	if (otherArrowNum > 1) { // there are other frames with the same number of arrows
		for (int i = 0; i < otherArrowNum; ++i) {
			if (arrowNums[numArrows[node]][i] != node) {
				if (onTopList[node].find(arrowNums[numArrows[node]][i]) == onTopList[node].end()) { // this frame is not on top of that frame
					if (!seen[combNum][arrowNums[numArrows[node]][i]]) {
						if (exists[arrowNums[numArrows[node]][i]]) {
							sameLevels.push_back(arrowNums[numArrows[node]][i]);
							//order[combNum].push_back(char(arrowNums[numArrows[node]][i] + 'A'));
							seen[combNum][arrowNums[numArrows[node]][i]] = true;
						}
					}
				}
			}
		}
	}
	//sameLevels.push_back(node);
	int numSameLevels = (int)sameLevels.size();
	vector<bool> picked(numSameLevels, false);
	vector<vector<int>> combinations;
	for (int i = 0; i < numSameLevels; ++i) {
		combinations.push_back(vector<int>());
		findCombinations(sameLevels, i, picked, (int)combinations.size() - 1, combinations);
	}
	int sameLevelsComb = (int)combinations.size();

	for (int i = 0; i < (int)leastArrowNode.size(); ++i) {
		if (i == 0) { // this is the first so we will make it part of the original strain
			if (sameLevelsComb > 0) {
				for (int j = 0; j < sameLevelsComb; ++j) { // for every of the sameLevels combinations
					// use them
					if (j > 0) {
						order.push_back(currentComb);
						numOfCombs += 1;
						seen.push_back(newSeenVect);
					}
					for (int k = 0; k < numSameLevels; ++k) {
						order[numOfCombs - 1].push_back(char(combinations[j][k] + 'A'));
					}
					findOrder(onTopList, numArrows, arrowNums, order, seen, exists, numOfCombs - 1, numOfCombs, leastArrowNode[i]);
				}
			}
			else {
				findOrder(onTopList, numArrows, arrowNums, order, seen, exists, numOfCombs - 1, numOfCombs, leastArrowNode[i]);
			}
		}
		else { // this is an extra strain
			if (sameLevelsComb > 0) {
				for (int j = 0; j < sameLevelsComb; ++j) {
					order.push_back(currentComb);
					numOfCombs += 1;
					seen.push_back(newSeenVect);
					for (int k = 0; k < numSameLevels; ++k) {
						order[numOfCombs - 1].push_back(char(combinations[j][k] + 'A'));
					}
					findOrder(onTopList, numArrows, arrowNums, order, seen, exists, numOfCombs - 1, numOfCombs, leastArrowNode[i]);
				}
			}
			else {
				order.push_back(currentComb);
				numOfCombs += 1;
				seen.push_back(newSeenVect);
				findOrder(onTopList, numArrows, arrowNums, order, seen, exists, numOfCombs - 1, numOfCombs, leastArrowNode[i]);
			}
		}
	}
	if ((int)leastArrowNode.size() == 0 && sameLevelsComb > 0) { // we reached the end but there are still same level nodes
		for (int j = 0; j < sameLevelsComb; ++j) {
			if (j > 0) {
				order.push_back(currentComb);
				numOfCombs += 1;
				seen.push_back(newSeenVect);
			}
			for (int k = 0; k < numSameLevels; ++k) {
				order[combNum + j].push_back(char(combinations[j][k] + 'A'));
			}
		}
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
	vector<vector<int>> boundaries(26, vector<int>(4, -1));
	vector<bool> exists(26, false);
	for (int i = 0; i < h; ++i) { // for every row
		for (int j = 0; j < w; ++j) { // for every column
			if (frameArray[i][j] != '.') { // if it is a letter
				int letter = frameArray[i][j] - 'A';
				exists[letter] = true;
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

	vector<unordered_set<int>> onTopList(26, unordered_set<int>());
	for (int i = 0; i < 26; ++i) {
		if (exists[i]) {
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
	}

	// find the number of arrows pointing to each frame
	vector<int> numArrows(26);
	for (int i = 0; i < 26; ++i) {
		for (auto it : onTopList[i]) {
			numArrows[it] += 1;
		}
	}
	vector<vector<int>> arrowFrames(26,vector<int>());
	for (int j = 0; j < 26; ++j) {
		arrowFrames[numArrows[j]].push_back(j);
	}

	// find the order of the frames
	vector<string> order;
	int numOfCombs = 0;
	vector<vector<bool>> seen;
	for (int i = 0; i < 26; ++i) { // find the start node
		if (exists[i]) {
			if (numArrows[i] == 0) { // we found one on top
				seen.push_back(vector<bool>(26, false));
				string nStr;
				order.push_back(nStr);
				numOfCombs += 1;
				findOrder(onTopList, numArrows, arrowFrames, order, seen, exists, numOfCombs - 1, numOfCombs, i);
			}
		}
	}
	for (int i = 0; i < (int)order.size(); ++i) {
		reverse(order[i].begin(), order[i].end());
	}
	sort(order.begin(), order.end());

	// print
	for (int i = 0; i < (int)order.size(); ++i) {
		fout << order[i] << endl;
	}
	return 0;
}