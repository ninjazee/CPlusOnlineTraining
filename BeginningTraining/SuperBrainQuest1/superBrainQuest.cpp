/*
This is a Super Brain Quest Problem.

The problem goes as follows:
Helen makes the conjecture that "all multiples of 6 have more factors than the two numbers on each side of the multiple." 
Is she correct? Why or why not?
Example: A multiple of 6 is 18, which has the six factors of 1, 2, 3, 6, 9, and 18. The two numbers on either side of 18 are 17 and 19, both of which are prime numbers and have two factors. Thus the multiple of 18 has more factors than the two factors on each side.

Prediction:
Helen is correct because six has 4 multiples (1, 2, 3, and 6) which is a large amount of multiples for its size.

*/

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void primeNums(int n, vector<int> &primes) {
	vector<int> numbers(n+1);
	for (int i = 0; i <= n; ++i) {
		numbers[i] = i;
	}

	numbers[0] = 0;
	numbers[1] = 0;
	for (int c = 2; c < n+1; ++c) {
		if (numbers[c] != 0) {
			int m = 2;
			while (c * m <= 10000) {
				numbers[c * m] = 0;
				m += 1;
			}
		}
	}

	for (int t = 0; t < n + 1; ++t) {
		if (numbers[t] != 0) {
			primes.push_back(t);
		}
	}
}

int main() {
	vector<int> primes;
	primes.reserve(10000);
	int n = 10000;
	primeNums(n, primes);
	for (int p : primes) {
		cout << p << " ";
	}
	return 0;
}

