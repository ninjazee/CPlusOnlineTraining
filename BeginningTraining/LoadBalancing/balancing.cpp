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

int loadBalancing(int n, vector<int> &xValues, vector<int> &yValues, vector<tuple<int, int>> &coords) {
	// sort the vectors
	sort(xValues.begin(), xValues.end());
	sort(yValues.begin(), yValues.end());
	sort(coords.begin(), coords.end(), TupleCompare<0>());

	// go through every vertical line
	int best = numeric_limits<int>::max();
	for (int i = 0; i < (int)xValues.size()-1; ++i) {
		int xValue = xValues[i];
		int xLine = xValue + 1;
		// go through every horizontal line
		for (int j = 0; j < (int)yValues.size()-1; ++j) {
			int yValue = yValues[j];
			int yLine = yValue + 1;
			int q1 = 0;
			int q2 = 0;
			int q3 = 0;
			int q4 = 0;
			for (int k = 0; k < (int)coords.size(); ++k) {
				tuple<int, int> coord = coords[k];
				// assign cows to quadrants created by lines
				if (get<0>(coord) > xLine && get<1>(coord) > yLine) {
					q1 += 1;
				}
				else if (get<0>(coord) < xLine && get<1>(coord) > yLine) {
					q2 += 1;
				}
				else if (get<0>(coord) < xLine && get<1>(coord) < yLine) {
					q3 += 1;
				}
				else if (get<0>(coord) > xLine && get<1>(coord) < yLine) {
					q4 += 1;
				}
			}
			// find which quadrant has the most
			int maximum = max(max(q1, q2), max(q3, q4));


			if (maximum < best) {
				best = maximum;
			}
		}
	}

	return best;
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

	fout << loadBalancing(n, xValues, yValues, coords) << endl;
	return 0;
}