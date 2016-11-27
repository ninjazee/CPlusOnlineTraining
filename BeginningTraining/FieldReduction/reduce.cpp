#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
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

int area(int leftBound, int rightBound, int upBound, int downBound) {
	int width = rightBound - leftBound;
	int height = downBound - upBound;
	int area = width * height;

	return area;
}

int fieldReduction(const vector<tuple<int, int, int>> &cowsx, const vector<tuple<int, int, int>> &cowsy) {
	int n = (int)cowsx.size();
	int leftBound = get<0>(cowsx[0]);
	int rightBound = get<0>(cowsx[n - 1]);
	int upBound = get<1>(cowsy[0]);
	int downBound = get<1>(cowsy[n - 1]);
	int l = get<0>(cowsx[1]);
	int r = get<0>(cowsx[n - 2]);
	int u = get<1>(cowsy[1]);
	int d = get<1>(cowsy[n - 2]);
	int smallest = area(leftBound, rightBound, upBound, downBound);

	if (leftBound == rightBound || upBound == downBound) {
		return 0;
	}
	else {
		for (int c = 0; c < n; ++c) {
			int x1 = leftBound;
			int x2 = rightBound;
			int y1 = upBound;
			int y2 = downBound;
			if (get<0>(cowsx[c]) == leftBound) {
				x1 = l;
			}
			if (get<0>(cowsx[c]) == rightBound) {
				x2 = r;
			}
			if (get<1>(cowsx[c]) == upBound) {
				y1 = u;
			}
			if (get<1>(cowsx[c]) == downBound) {
				y2 = d;
			}

			int newArea = area(x1, x2, y1, y2);
			if (newArea < smallest) {
				smallest = newArea;
			}
		}
	}

	return smallest;
}

int main() {
	ofstream fout("reduce.out");
	ifstream fin("reduce.in");
	int n;
	fin >> n;
	vector<tuple<int, int, int>> cowsx(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		fin >> x >> y;
		auto cow = make_tuple(x, y, i);
		cowsx[i] = cow;
	}
	vector<tuple<int, int, int>> cowsy(cowsx);
	sort(cowsx.begin(), cowsx.end(), TupleCompare<0>());
	sort(cowsy.begin(), cowsy.end(), TupleCompare<1>());

	int leftBound = get<0>(cowsx[0]);
	int rightBound = get<0>(cowsx[n - 1]);
	int upBound = get<1>(cowsy[0]);
	int downBound = get<1>(cowsy[n - 1]);
	int a = area(leftBound, rightBound, upBound, downBound);
	int area = fieldReduction(cowsx, cowsy);
	fout << area << endl;
	return 0;
}
