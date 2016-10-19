#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
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

int loadBalancing(vector<int> &xValues, vector<int> &yValues, vector<tuple<int, int>> &coords) {
	sort(xValues.begin(), xValues.end());
	sort(yValues.begin(), yValues.end());
	sort(coords.begin(), coords.end(), TupleCompare<0>());

	int xBest = 0;
	for (int x : xValues) {
		int vLine = x + 1;
	}
}

int main() {
	ofstream fout("balancing.out");
	ifstream fin("balancing.in");
	int n, b;
	fin >> n >> b;

	vector<int> xValues(n);
	vector<int> yValues(n);
	vector<tuple<int, int>> coords(n);

	for (int i = 0; i < n; ++i) {
		int xVal, yVal;
		fin >> xVal >> yVal;
		xValues[i] = xVal;
		yValues[i] = yVal;
		auto coord = make_tuple(xVal, yVal);
		coords[i] = coord;
	}

	fout << loadBalancing(xValues, yValues, coords) << endl;
	return 0;
}