#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdio.h>

using namespace std;

int count_digits(int num) {
	int count = 0;
	while (num != 0) {
		count++;
		num /= 10;
	}
	return count;
}

int power(const int base, const int power) {
	int b = base;
	for (int i = 0; i < power - 1; ++i) {
		b *= base;
	}
	return b;
}

void countsheep(const int n, const int c) {
	if (n == 0) {
		cout << "Case #" << c << ": INSOMNIA" << endl;
	}
	else {
		int i = 1; // which number you multiply n by
		vector<bool> seen(10, false); // keeps track of digits which you have seen
		int seennum = 0; // how many numbers you have seen
		while (seennum < 10) {
			int currnum = i * n;
			int digitcount = count_digits(currnum);

			if (digitcount == 1) { // only one digit
				if (seen[currnum] == false) { // if not seen
					// add it to the seen digits
					seennum += 1;
					seen[currnum] = true;
				}
			}
			else { // more than one digit
				int alreadycounted = 0;
				for (int j = 1; j < count_digits(currnum) + 1; ++j) { // for each digit
					int digit;
					if (j == 1) {
						digit = currnum % power(10, j);
					}
					else {
						digit = ((currnum % power(10, j) - alreadycounted) / power(10, j - 1));
					}
					if (seen[digit] == false) { // if not seen
						// add it to the seen digits
						seennum += 1;
						seen[digit] = true;
					}
					alreadycounted = currnum % power(10, j);
				}
			}
			i += 1;
		}
		cout << "Case #" << c << ": " << ((i - 1) * n) << endl;
	}
}

int main() {
	int t;
	cin >> t;
	
	for (int a = 1; a <= t; ++a) {
		int n;
		cin >> n;
		countsheep(n, a);
	}

	return 0;
}