/*
ID: kml111
PROG: heritage
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <strstream>

using namespace std;

void generateTree(const string &inOrder, const string &preOrder, const int level, ofstream &fout) {
	char root = preOrder[0]; // root
	//tree[level].push_back(root);
	int l = (int)inOrder.length();
	
	if (l > 1) {
		int p = 0;
		while (inOrder[p] != root) {
			p += 1;
		}
		string newInOrderL(inOrder, 0, p);
		string newPreOrderL(preOrder, 1, p);

		generateTree(newInOrderL, newPreOrderL, level + 1, fout);

		string newInOrderR(inOrder.begin() + p + 1, inOrder.begin() + l);
		string newPreOrderR(preOrder.begin() + p + 1, preOrder.begin() + l);

		generateTree(newInOrderR, newPreOrderR, level + 1, fout);
		fout << root;
	}
	else {
		fout << inOrder;
	}
}

int main() {
	ofstream fout("heritage.out");
	ifstream fin("heritage.in");
	string inOrder;
	fin >> inOrder;
	string preOrder;
	fin >> preOrder;

	vector<vector<char>> tree(26);

	generateTree(inOrder, preOrder, 0, fout);
	fout << endl;
	return 0;
}