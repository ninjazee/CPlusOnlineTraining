#include <fstream>
#include <iostream>

using namespace std;

int milkPails(int x, int y, int m) {
	int highest = 0;
	int xCount = 0;
	int yCount = 0;
	while ((xCount * x) <= m) {
		int yCount = 0;
		int xVal = xCount * x;
		yCount = (m - xVal) / y;
		int yVal = yCount * y;
		if ((xVal + yVal) > highest) {
			highest = xVal + yVal;
		}
		xCount += 1;
	}
	return highest;
}

int main() {
	ofstream fout("pails.out");
	ifstream fin("pails.in");
	int x, y, m;
	fin >> x >> y >> m;

	fout << milkPails(x, y, m) << endl;
	return 0;
}