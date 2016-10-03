// paint

#include <iostream>
#include <fstream>


using namespace std;

int paint_fence(int a, int b, int c, int d) {
	int subtraction;
	if (a <= c) {
		if (b >= d) {
			subtraction = d - c;
		}
		else {
			if (b <= c) {
				subtraction = 0;
			}
			else {
				subtraction = b - c;
			}
		}
	}
	else {
		if (b <= d) {
			subtraction = b - a;
		}
		else {
			if (d <= a) {
				subtraction = 0;
			}
			else {
				subtraction = d - a;
			}
		}
		
	}
	int aToB = b - a;
	int cToD = d - c;
	int fence_painted = aToB + cToD - subtraction;
	return fence_painted;
}

int main() {
	ofstream fout("paint.out");
	ifstream fin("paint.in");
	int a, b, c, d;
	fin >> a >> b;
	fin	>> c >> d;

	fout << paint_fence(a, b, c, d) << endl;
	return 0;
}