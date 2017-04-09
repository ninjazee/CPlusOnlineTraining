#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int oversizedPancakeFlipper(string &s, const int k) {
	int flips = 0;
	int numPancakes = (int)s.length();
	for (int i = 0; i < numPancakes; ++i) {
		if (i > numPancakes - k && s[i] == '-') { // cannot flip anymore
			return -1;
		}
		else {
			if (s[i] == '-') { // pancake is on its blank side
				for (int j = 0; j < k; ++j) { // flip k pancakes starting from this pancake with oversized pancake flipper
					if (s[i + j] == '-') {
						s[i + j] = '+';
					}
					else {
						s[i + j] = '-';
					}
				}
				flips += 1;
			}
		}
	}
	return flips;
}

int main() {
	int t;
	cin >> t;
	for (int a = 0; a < t; ++a) {
		string s;
		int k;
		cin >> s;
		cin >> k;
		int flips = oversizedPancakeFlipper(s, k);
		cout << "Case #" << a + 1 << ": ";
		if (flips == -1) {
			cout << "IMPOSSIBLE" << endl;
		}
		else {
			cout << flips << endl;
		}
	}
	return 0;
}