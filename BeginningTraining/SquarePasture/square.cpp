#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
	ofstream fout("square.out");
	ifstream fin("square.in");
	int ax1, ay1, ax2, ay2;
	int bx1, by1, bx2, by2;
	fin >> ax1 >> ay1 >> ax2 >> ay2;
	fin >> bx1 >> by1 >> bx2 >> by2;
	int maximumx = max(ax2, bx2);
	int minimumx = min(ax1, bx1);
	int maximumy = max(ay2, by2);
	int minimumy = min(ay1, by1);
	int maximumSideLength = max((maximumx - minimumx), (maximumy - minimumy));
	fout << (maximumSideLength)*(maximumSideLength) << endl;
	return 0;
}
