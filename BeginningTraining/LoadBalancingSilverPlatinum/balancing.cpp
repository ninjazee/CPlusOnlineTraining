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

int loadBalancing(int n, vector<int> &xValues, vector<tuple<int, int>> &coords) {
	// sort the vectors
	sort(xValues.begin(), xValues.end());
	sort(coords.begin(), coords.end(), TupleCompare<1>());

	// go through every vertical line
	int best = numeric_limits<int>::max();
	for (int i = 0; i < (int)coords.size() - 1; ++i) {
		tuple<int, int> coord = coords[i];
		int xLine = get<1>(coord) + 1;
		vector<int> q1(n);
		vector<int> q2(n);
		vector<int> q3(n);
		vector<int> q4(n);
		// go through every horizontal line
		int idx = 0; 
		bool bDoubleYValue12 = false; 
		for (int j = 0; j < (int)xValues.size(); ++j) {
			tuple<int, int> xcoord = coords[j];
			int xVal = get<0>(xcoord);
			bDoubleYValue12 = (j > 0)? get<1>(coords[j]) == get<1>(coords[j - 1]) : true;
			if (xVal < xLine) {
				q1[idx] = bDoubleYValue12 ? q1[idx - 1] + 1 : q1[idx] + 1;
				q2[idx] = bDoubleYValue12 ? q2[idx - 1] : q2[idx];
			}
			else {
				q2[idx] += idx > 0 ? q2[idx - 1] + 1 : q2[idx] + 1;
				q1[idx] += idx > 0 ? q1[idx - 1] : q1[idx];
			}
			
			if (!bDoubleYValue12) {
				idx++; 
			}
		}

		int idx1 = idx; 
		bool bDoubleYValue34 = 0;
		for (int k = (int)xValues.size() - 1; k >= 0; --k) {
			tuple<int, int> ycoord = coords[k];
			int xVal = get<0>(ycoord);
			bDoubleYValue34 = (k < idx) ? get<1>(coords[k]) == get<1>(coords[k + 1]) : true;
			if (xVal < xLine) {
				q3[idx1] += bDoubleYValue34 ? q3[idx1 + 1] + 1: q3[idx1] + 1;
				q4[idx1] += bDoubleYValue34 ? q4[idx1 + 1] : q3[idx1];
				/*
				q3[k] = b > 0? q3[b - 1] + 1 : 1;
				q4[k] = b > 0? q4[b - 1] : 0;
				*/
			}
			else {
				q4[idx1] += bDoubleYValue34 ? q4[idx1 + 1] + 1 : q4[idx] + 1;
				q3[idx1] += bDoubleYValue34 ? q3[idx1 + 1] : q4[idx];
				/*
				q4[k] = b > 0 ? q4[b - 1] + 1 : 1;
				q3[k] = b > 0 ? q3[b - 1] : 0;
				*/
			}

			bDoubleYValue34 = k > 0 ? get<1>(coords[k]) == get<1>(coords[k - 1]) : false;
			if (!bDoubleYValue34) {
				idx1--; 
			}
		}

		int maxIdx = bDoubleYValue12 > bDoubleYValue34 ? idx + 1 : idx; 
		for (int l = 0; l < maxIdx; ++l) {
			int maximum = max(max(q1[l], q2[l]), max(q3[l], q4[l]));
			if (maximum < best ) {
				best = maximum;
			}
		}
	}

	return best;
}

int main() {
	ofstream fout("balancing.out");
	ifstream fin("balancing.in");
	int n;
	fin >> n;

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

	fout << loadBalancing(n, xValues, coords) << endl;
	return 0;
}