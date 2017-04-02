#include <string>
#include <vector>
#include <iostream>

using namespace std;

int commonCharacterCount(string s1, string s2) {
	int commonCharacters = 0;
	vector<bool> paired1((int)s1.size(), false);
	vector<bool> paired2((int)s2.size(), false);
	for (int i = 0; i < (int)s1.size(); ++i) {
		if (paired1[i] == false) {
			for (int j = 0; j < (int)s2.size(); ++j) {
				if (paired1[i] == false && paired2[j] == false) {
					if (s1[i] == s2[j]) {
						paired1[i] = true;
						paired2[j] = true;
						commonCharacters += 1;
					}
				}
			}
		}

	}
	return commonCharacters;
}

int main() {
	string s1("aabcc");
	string s2("adcaa");
	cout << commonCharacterCount(s1, s2) << endl;
	return 0;
}