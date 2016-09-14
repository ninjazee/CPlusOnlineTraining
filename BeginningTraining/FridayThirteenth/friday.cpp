/*
ID: kml111
PROG: friday
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

using namespace std;

int main() {
	ofstream fout("friday.out");
	ifstream fin("friday.in");
	int n;
	int date = 0;
	fin >> n;
	array<int, 7> dayFrequency { 0, 0, 0, 0, 0, 0, 0 };
	array<int, 12> monthDays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int nYears = n + 1900;
	for (int y = 1900; y < nYears; ++y) {
		for (int m = 0; m < 12; ++m) {
			int days = monthDays[m];
			if (m == 1 && y % 4 == 0) {
				if (y % 100 == 0) {
					if (y % 400 == 0) {
						days += 0;
					}
					else {
						days -= 1;
					}
				}
				days += 1;
			}
			for (int d = 0; d < days; ++d) {
				if (d == 12) {
					dayFrequency[date] += 1;
				}
				date = (date + 1) % 7;
			}
		}
	}
	fout << dayFrequency[5] << " " << dayFrequency[6] << " " << dayFrequency[0] << " " << dayFrequency[1] << " " << dayFrequency[2] << " " << dayFrequency[3] << " " << dayFrequency[4] << endl;
	return 0;
}
