#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

bool compareNames(tuple<int, string> i, tuple<int, string> j) { return (get<1>(i) < get<1>(j)); }

bool compareNamesRev(tuple<int, string> i, tuple<int, string> j) { return (get<1>(i) > get<1>(j)); }

void sortNames(vector<string> &vect) {
	sort (vect.begin(), vect.end());
}

void sortNamesID(vector<tuple<int, string>> &names) 
{
	sort(names.begin(), names.end(), compareNames);
}

void sortNamesIDRev(vector<tuple<int, string>> &names)
{
	sort(names.begin(), names.end(), compareNamesRev);
}

int main() {
	//ofstream fout("sortnames.out");
	ifstream fin("sortnames.in");
	int np;
	fin >> np;
	vector<tuple<int, string>> names(np);
	for (int i = 0; i < np; ++i) {
		string name;
		int id;
		fin >> id >> name;
		names[i] = make_tuple(id, name);

	}
	sortNamesIDRev(names);
	for (int j = 0; j < np; ++j) {
		cout << get<0>(names[j]) << endl;
	}
	return 0;
}