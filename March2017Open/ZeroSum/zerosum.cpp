/*
ID: kml111
PROG: zerosum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void generateCombinations(const int n, const int current, string &combination, vector<string> &combinations) { // generate all possible combinations of operators
	if (current == n - 1) { // combination is finished
		combinations.push_back(combination);
	}
	else {
		// operator is +
		combination[(current * 2) + 1] = '+';
		generateCombinations(n, current + 1, combination, combinations);

		// operator is -
		combination[(current * 2) + 1] = '-';
		generateCombinations(n, current + 1, combination, combinations);

		// operator is _
		combination[(current * 2) + 1] = ' ';
		generateCombinations(n, current + 1, combination, combinations);
	}
}

void zeroSum(vector<string> &combinations) {
	for (int i = 0; i < (int)combinations.size(); ++i) { // for every combination
		//int a = combinations[i][0] - '0';
		int b = combinations[i][2] - '0';
		int l = (int)combinations[i].length() / 2;
		int total = combinations[i][0] - '0';
		int j = 0;
		while (j <= l - 1) {
			//a = combinations[i][j * 2];
			//b = combinations[i][(j * 2) + 2];
			while (combinations[i][(j * 2) + 1] == ' ' && j < l - 1) { // operator is a space
				total = (total * 10) + b;
				j += 1;
				b = combinations[i][(j * 2) + 2] - '0';
			}
			int k = j + 1;
			bool skipOperator = false;
			while (combinations[i][(k * 2) + 1] == ' ' && k <= l) { // next operator is a space
				skipOperator = true;
				b = (b * 10) + (combinations[i][(k * 2) + 2] - '0');
				k += 1;
			}
				
			switch (combinations[i][(j * 2) + 1]) {
			case '+': 
				total += b;
				break;
			case '-':
				total -= b;
				break;
			}
			if (skipOperator) {
				j = k;
			}
			else {
				j += 1;
			}
			if (j <= l - 1 && k <= l - 1) {
				b = combinations[i][(j * 2) + 2] - '0';
			}
		}
		if (total != 0) {
			combinations[i] = "x";
		}
	}
}

int main() {
	ofstream fout("zerosum.out");
	ifstream fin("zerosum.in");
	int n;
	fin >> n;
	
	// create a template
	string s;
	for (int i = 0; i < (n * 2) - 1; ++i) { // for each character space
		if (i % 2 == 0) { // even numbered character space; number
			s.push_back(((i + 2) / 2) + '0');
		}
		else { // odd numbered character space; operator
			s.push_back('.');
		}
	}

	vector<string> combinations;
	generateCombinations(n, 0, s, combinations);

	zeroSum(combinations);

	sort(combinations.begin(), combinations.end());
	for (int j = 0; j < (int)combinations.size(); ++j) {
		if (combinations[j] != "x") {
			fout << combinations[j] << endl;
		}
	}
	return 0;
}