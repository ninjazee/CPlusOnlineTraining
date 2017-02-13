#include <iostream>
#include <fstream>
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

int helpCross(vector<int> &chickens, vector<tuple<int, int>> &cows/*, vector<bool> &npaired*/) {
	sort(chickens.begin(), chickens.end());
	sort(cows.begin(), cows.end(), TupleCompare<0>());

	int c = (int)chickens.size();
	int n = (int)cows.size();

	int j = 0;
	int pairs = 0;
	for (int i = 0; i < c; ++i) {
		if (j > n - 1) {
			break;
		}
		else {
			while (j <= n - 1 && get<0>(cows[j]) <= chickens[i]) {
				//if (npaired[cowspot] == false) {
				if (get<1>(cows[j]) >= chickens[i]) {
					pairs += 1;
					//npaired[cowspot] = true;
					j += 1;
					break;
				}
				//}
				j += 1;
			}
		}
	}

	return pairs;
}

int helpCross2(vector<int> &chickens, vector<tuple<int, int>> &cows/*, vector<bool> &npaired*/) {
	sort(chickens.begin(), chickens.end());
	sort(cows.begin(), cows.end(), TupleCompare<0>());

	vector<tuple<int, int>> cows2 (cows);

	sort(cows2.begin(), cows2.end(), TupleCompare<1>());

	int c = (int)chickens.size();
	int n = (int)cows.size();

	int j = 0;
	int pairs = 0;
	for (int i = 0; i < c; ++i) {
		if (j > n - 1) {
			break;
		}
		else {
			while (j <= n - 1 && get<0>(cows[j]) <= chickens[i]) {
				//if (npaired[cowspot] == false) {
				if (get<1>(cows[j]) >= chickens[i]) {
					pairs += 1;
					//npaired[cowspot] = true;
					j += 1;
					break;
				}
				//}
				j += 1;
			}
		}
	}

	int k = 0;
	int pairs2 = 0;
	for (int l = 0; l < c; ++l) {
		if (k > n - 1) {
			break;
		}
		else {
			while (k <= n - 1 && get<0>(cows2[k]) <= chickens[l]) {
				//if (npaired[cowspot] == false) {
				if (get<1>(cows2[k]) >= chickens[l]) {
					pairs2 += 1;
					//npaired[cowspot] = true;
					k += 1;
					break;
				}
				//}
				k += 1;
			}
		}
	}

	if (pairs2 > pairs) {
		return pairs2;
	}
	else {
		return pairs;
	}
}

int main() {
	ofstream fout("helpcross.out");
	ifstream fin("helpcross.in");
	int c, n;
	fin >> c >> n;
	vector<int> chickens(c);
	for (int x = 0; x < c; ++x) {
		int t;
		fin >> t;
		chickens[x] = t;
	}
	vector<tuple<int, int>> cows(n);
	for (int y = 0; y < n; ++y) {
		int a, b;
		fin >> a >> b;
		cows[y] = make_tuple(a, b);
	}

	//vector<bool> npaired(n, false);

	fout << helpCross(chickens, cows/*, npaired*/) << endl;
	return 0;
}