#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
	}
};

string notlast(vector<tuple<string, int>> &cowmilk) {
	sort(cowmilk.begin(), cowmilk.end(), TupleCompare<0>());
	int i = 1;
	while (i < (int)cowmilk.size()) {
		if (get<0>(cowmilk[i]) == get<0>(cowmilk[i - 1])) {
			get<1>(cowmilk[i - 1]) += get<1>(cowmilk[i]);
			cowmilk.erase(cowmilk.begin() + i);
		}
		else {
			i += 1;
		}
	}

	if ((int)cowmilk.size() < 7) {
		int a = 0;
		int l = get<1>(cowmilk[0]);
		while (a < (int)cowmilk.size() && get<1>(cowmilk[a]) == l) {
			a += 1;
		}
		if (a == 1) {
			return get<0>(cowmilk[0]);
		}
		else {
			return "Tie";
		}
	}

	sort(cowmilk.begin(), cowmilk.end(), TupleCompare<1>());
	int last = get<1>(cowmilk[0]);
	int j = 0;
	while (j < (int)cowmilk.size() && get<1>(cowmilk[j]) == last) {
		j += 1;
	}
	if (j == (int)cowmilk.size()) {
		return "Tie";
	}
	else if (j == (int)cowmilk.size() - 1) {
		return get<0>(cowmilk[(int)cowmilk.size() - 1]);
	}

	int k = j;
	int slast = get<1>(cowmilk[j]);
	while (get<1>(cowmilk[k]) == slast) {
		k += 1;
	}

	if ((k - j) == 1) {
		return get<0>(cowmilk[k - 1]);
	}
	else {
		return "Tie";
	}
}

int main() {
	ofstream fout("notlast.out");
	ifstream fin("notlast.in");
	int n;
	fin >> n;
	vector<tuple<string, int>> cowmilk(n);
	for (int x = 0; x < n; ++x) {
		string cow;
		int milk;
		fin >> cow >> milk;
		cowmilk[x] = make_tuple(cow, milk);
	}
	fout << notlast(cowmilk) << endl;
	return 0;
}