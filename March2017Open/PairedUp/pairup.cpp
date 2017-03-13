#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>

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

int pairup(vector<tuple<int, int>> &cows, int &max, const int i, const int j) {
	int total = get<0>(cows[i]) + get<0>(cows[j]); // total of cow milking time

	int minmany;
	int maxmany;
	int maxnum = -1;
	if (get<1>(cows[i]) > get<1>(cows[j])) {
		maxnum = i;
		get<1>(cows[maxnum]) = get<1>(cows[i]) - get<1>(cows[j]);
		if (total > max) {
			max = total;
		}
	}
	else if (get<1>(cows[i]) < get<1>(cows[j])) {
		maxnum = j;
		get<1>(cows[maxnum]) = get<1>(cows[j]) - get<1>(cows[i]);
		if (total > max) {
			max = total;
		}
	}
	else {
		if (get<1>(cows[i]) != 0) {
			if (total > max) {
				max = total;
			}
		}
		get<1>(cows[i]) = 0;
		get<1>(cows[j]) = 0;
	}
	

	return maxnum;
}

int main() {
	ofstream fout("pairup.out");
	ifstream fin("pairup.in");
	int n;
	fin >> n;
	
	vector<tuple<int, int>> cows(n);
	for (int a = 0; a < n; ++a) {
		int x, y;
		fin >> x >> y;
		cows[a] = make_tuple(y, x);
	}

	sort(cows.begin(), cows.end(), TupleCompare<0>());

	int max = 0;
	int i = 0;
	int j = (int)cows.size() - 1;
	do {
		int maxnum = pairup(cows, max, i, j);

		if (maxnum == -1) {
			i += 1;
			j -= 1;
		}
		else if (maxnum == i) {
			j -= 1;
		}
		else {
			i += 1;
		}
	} while (i < (int)cows.size() && j > 0 && get<1>(cows[i]) != 0);

	cout << max << endl;
	return 0;
}