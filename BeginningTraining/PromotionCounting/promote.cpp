#include <iostream>
#include <fstream>
#include <array>

using namespace std;

array<int, 3> promote(array<int, 4> before, array<int, 4> after) {
	array<int, 3> retVals = { 0, 0, 0 };
	int bDiff = after[1] - before[1];
	int cDiff = after[2] - before[2];
	int dDiff = after[3] - before[3];
	retVals[0] += dDiff;
	retVals[1] += dDiff;
	retVals[2] += dDiff;
	retVals[0] += cDiff;
	retVals[1] += cDiff;
	retVals[0] += bDiff;
	return retVals;
}

int main() {
	ofstream fout("promote.out");
	ifstream fin("promote.in");
	int aBefore, aAfter, bBefore, bAfter, cBefore, cAfter, dBefore, dAfter;
	fin >> aBefore >> aAfter >> bBefore >> bAfter >> cBefore >> cAfter >> dBefore >> dAfter;
	array<int, 4> before = { aBefore, bBefore, cBefore, dBefore };
	array<int, 4> after = { aAfter, bAfter, cAfter, dAfter };
	array<int, 3> promotions = promote(before, after);

	fout << promotions[0] << endl << promotions[1] << endl << promotions[2] << endl;
	return 0;
}