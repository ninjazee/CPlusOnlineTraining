#include <vector>
#include <iostream>

using namespace std;

bool almostIncreasingSequence(vector<int> sequence) {
	int n = (int)sequence.size();
	for (int i = 0; i < n; ++i) { // i is the one I will erase
		bool works = true;
		for (int j = 0; j < n - 1; ++j) { // for every number
			if (j != i) { // skip over i
				if (j + 1 == i && i < n - 1) {
					if (sequence[j] >= sequence[j + 2]) {
						works = false;
						break;
					}
				}
				else {
					if (sequence[j] >= sequence[j + 1]) {
						works = false;
						break;
					}
				}
			}
		}
		if (works) {
			return true;
		}
	}
	return false;
}

bool almostIncreasingSequence2(vector<int> sequence) {
	vector<bool> seen(100000, 0);
	int notIncreasing = 0;
	int n = (int)sequence.size();
	seen[sequence[0]] = true;
	for (int i = 0; i < n - 1; ++i) { // i is the one I will erase
		if (sequence[i] >= sequence[i + 1] || seen[sequence[i + 1]] == true) {
			notIncreasing += 1;
		}
		if (notIncreasing > 1) {
			return false;
		}
		seen[sequence[i + 1]] = true;
	}
	return true;
}

bool almostIncreasingSequence3(vector<int> sequence) {
	vector<bool> seenpos(100000, 0);
	vector<bool> seenneg(100000, 0);
	int notIncreasing = 0;
	int n = (int)sequence.size();
	if (sequence[0] < 0) {
		seenneg[sequence[0]] = true;
	}
	else if (sequence[0] > 0) {
		seenpos[sequence[0]] = true;
	}
	else {
		seenpos[sequence[0]] = true;
		seenneg[sequence[0]] = true;
	}
	for (int i = 0; i < n - 1; ++i) { // i is the one I will erase
		if (sequence[i + 1] > 0) {
			if (sequence[i] >= sequence[i + 1] || seenpos[sequence[i + 1]] == true) {
				notIncreasing += 1;
			}
			if (notIncreasing > 1) {
				return false;
			}
			seenpos[sequence[i + 1]] = true;
		}
		else if (sequence[i + 1] < 0) {
			if (sequence[i] >= sequence[i + 1] || seenneg[sequence[i + 1]] == true) {
				notIncreasing += 1;
			}
			if (notIncreasing > 1) {
				return false;
			}
			seenneg[sequence[i + 1]] = true;
		}
		else {
			if (sequence[i] >= sequence[i + 1] || seenpos[sequence[i + 1]] == true) {
				notIncreasing += 1;
			}
			if (notIncreasing > 1) {
				return false;
			}
			seenpos[sequence[i + 1]] = true;
			seenneg[sequence[i + 1]] = true;
		}
	}
	return true;
}

int main() {
	int s[] = { 1, 2, 1, 2 };
	vector<int> sequence(s, s + sizeof(s) / sizeof(int));
	if (almostIncreasingSequence(sequence)) {
		cout << true << endl;
	}
	else {
		cout << false << endl;
	}
	return 0;
}