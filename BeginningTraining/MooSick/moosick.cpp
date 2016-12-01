#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void minusMin(vector<int> &vec)
{
	int minval = vec[0];
	for (int i = 0; i < (int)vec.size(); i++)
		vec[i] -= minval; 
}

void mooSick(vector<int> &song, vector<int> &chord, vector<int> &indexes) {
	sort(chord.begin(), chord.end());
	int n = (int)song.size();
	int c = (int)chord.size();
	for (int k = 0; k < n - c + 1; ++k) {
		vector<int> section(c);
		for (int m = 0; m < c; ++m) {
			section[m] = song[m + k];
		}
		sort(section.begin(), section.end());
		int gap = section[0] - chord[0];
		if (section == chord) {
			indexes.push_back(k);
		}
		else {
			bool transpose = true;
			int n = 0;
			while (transpose == true && n < c) {
				if (section[n] - chord[n] == gap) {
					n += 1;
				}
				else {
					transpose = false;
					break;
				}
			}
			if (transpose == true) {
				indexes.push_back(k);
			}
		}
	}
}

int main() {
	ofstream fout("moosick.out");
	ifstream fin("moosick.in");
	int n;
	fin >> n;
	vector<int> song(n);
	for (int i = 0; i < n; ++i) {
		int note;
		fin >> note;
		song[i] = note;
	}
	int c;
	fin >> c;
	vector<int> chord(c);
	for (int j = 0; j < c; ++j) {
		int note;
		fin >> note;
		chord[j] = note;
	}
	vector<int> indexes;
	mooSick(song, chord, indexes);
	int k = (int)indexes.size();
	cout << k << endl;
	for (int p = 0; p < k; ++p) {
		cout << indexes[p] + 1 << endl;
	}
	return 0;
}
