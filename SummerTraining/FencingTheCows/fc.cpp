/*
ID: kml111
PROG: fc
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

#define PI 3.14159265

template<int M, template<typename> class F = std::less>
struct TupleCompare
{
	template<typename T>
	bool operator()(T const &t1, T const &t2)
	{
		return F<typename tuple_element<M, T>::type>()(std::get<M>(t1), std::get<M>(t2));
	}
};

double zcrossprod(const double ux, const double uy, const double uz, const double vx, const double vy, const double vz) {
	return (uy * vz - vy * uz) + (uz * vx - vz * ux) + (ux * vy - vx * uy);
}

int main() {
	ofstream fout("fc.out");
	ifstream fin("fc.in");
	int n;
	fin >> n;
	vector<tuple<double, double>> grazingSpots(n);
	for (int a = 0; a < n; ++a) {
		double xi, yi;
		fin >> xi >> yi;
		grazingSpots[a] = make_tuple(xi, yi);
	}

	// calculate the angle each point makes with a middle point (from 0 to 360)
	double midx = 0;
	double midy = 0;
	for (int i = 0; i < n; ++i) {
		double xi = get<0>(grazingSpots[i]);
		double yi = get<1>(grazingSpots[i]);
		midx += xi / n;
		midy += yi / n;
	}
	vector<tuple<int, double>> anglePerm(n);
	//vector<int> perm(n);
	for (int i = 0; i < n; ++i) {
		double xi = get<0>(grazingSpots[i]);
		double yi = get<1>(grazingSpots[i]);
		get<1>(anglePerm[i]) = atan2(yi - midy, xi - midx) * 180.0 / PI;
		get<0>(anglePerm[i]) = i;
	}

	// sort points based on angle values
	sort(anglePerm.begin(), anglePerm.end(), TupleCompare<1>());

	// start making hull
	vector<int> hull(n);
	hull[0] = get<0>(anglePerm[0]);
	hull[1] = get<0>(anglePerm[1]);
	int hullpos = 2;
	for (int p = 0; p < n - 1; ++p) {
		// while the angle is larger than 180 degrees (concave)
		while (hullpos > 1 && zcrossprod(get<0>(grazingSpots[hull[hullpos - 2] - hull[hullpos - 1]]), get<1>(grazingSpots[hull[hullpos - 2] - hull[hullpos - 1]]), 0, get<0>(grazingSpots[hull[hullpos - 1] - get<0>(anglePerm[p])]), get<1>(grazingSpots[hull[hullpos - 1] - get<0>(anglePerm[p])]), 0) < 0) {
			hullpos -= 1;
		}
		hull[hullpos] = get<0>(anglePerm[p]);
		hullpos += 1;
	}

	// add the last point
	int p = get<0>(anglePerm[n - 1]);
	while (hullpos > 1 && zcrossprod(get<0>(grazingSpots[hull[hullpos - 2] - hull[hullpos - 1]]), get<1>(grazingSpots[hull[hullpos - 2] - hull[hullpos - 1]]), 0, get<0>(grazingSpots[hull[hullpos - 1] - p]), get<1>(grazingSpots[hull[hullpos - 1] - p]), 0) < 0) {
		hullpos -= 1;
	}

	int hullstart = 0;
	bool flag = false;
	do {
		bool flag = false;
		if (hullpos - hullstart >= 2 && zcrossprod(get<0>(grazingSpots[p - hull[hullpos - 1]]), get<1>(grazingSpots[p - hull[hullpos - 1]]), 0, get<0>(grazingSpots[hull[hullstart] - p]), get<0>(grazingSpots[hull[hullstart] - p]), 0)) {
			p = hull[hullpos - 1];
			hullpos -= 1;
			flag = true;
		}
		if (hullpos - hullstart >= 2 && zcrossprod(get<0>(grazingSpots[hull[hullstart] - p]), get<1>(grazingSpots[hull[hullstart] - p]), 0, get<0>(grazingSpots[hull[hullstart + 1] - hull[hullstart]]), get<0>(grazingSpots[hull[hullstart + 1] - hull[hullstart]]), 0)) {
			hullstart += 1;
			flag = true;
		}
	} while (flag);
	hull[hullpos] = p;
	hullpos += 1;


	return 0;
}