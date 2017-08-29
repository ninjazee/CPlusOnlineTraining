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
#include <unordered_set>
#include <iomanip>

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

int count_digits(double number) {
	int count = 0;
	int num = (int)number;
	while (num != 0) {
		count++;
		num /= 10;
	}
	return count;
}

double zcrossprod(const double ux, const double uy, const double uz, const double vx, const double vy, const double vz) {
	return (uy * vz - vy * uz) + (uz * vx - vz * ux) + (ux * vy - vx * uy);
}

double zcrossprod2(const tuple<double, double> p1, const tuple<double, double> p2, const tuple<double, double> p3) {
	double ux = get<0>(p2) - get<0>(p1);
	double uy = get<1>(p2) - get<1>(p1);
	double vx = get<0>(p3) - get<0>(p2);
	double vy = get<1>(p3) - get<1>(p2);
	return ux * vy - vx * uy;
}

void grahamScan(const vector<tuple<double, double>> &grazingSpots, vector<tuple<double, double>> &s) {
	int n = (int)grazingSpots.size();
	// let p[0] be the point in Q with the minimum y-coordinate, or the leftmost such point in case of a tie
	vector<tuple<double, double>> p;
	p.push_back(grazingSpots[0]);

	// let p[1]; p[2]; . . . ;p[m] be the remaining points in Q, sorted by polar angle in counterclockwise order around p[0] (if more than one point has the same angle, remove all but the one that is farthest from p[0])
	tuple<int, double> example = make_tuple(-1, -1);
	vector<tuple<int, double>> angle(n, example);
	unordered_set<double> seen;
	for (int i = 1; i < n; ++i) {
		double xi = get<0>(grazingSpots[i]);
		double yi = get<1>(grazingSpots[i]);
		double tanVal = atan2(yi - get<1>(p[0]), xi - get<0>(p[0])) * 180.0 / PI;
		if (seen.find(tanVal) == seen.end()) {
			get<1>(angle[i]) = tanVal;
			get<0>(angle[i]) = i;
			seen.insert(tanVal);
		}
	}
	sort(angle.begin(), angle.end(), TupleCompare<1>());
	for (int a = 0; a < n; ++a) {
		if (get<0>(angle[a]) != -1) { // this node actually exists
			// add it to p
			p.push_back(grazingSpots[get<0>(angle[a])]);
		}
	}
	/*
	int numNodes = (int)p.size();
	vector<tuple<double, double>> xy(numNodes - 1);
	for (int b = 1; b < numNodes; ++b) {
		double x = abs(get<0>(p[b - 1]) - get<0>(p[b]));
		double y = abs(get<1>(p[b - 1]) - get<1>(p[b]));
		xy[b - 1] = make_tuple(x, y);
	}
	*/

	s.push_back(p[0]);
	s.push_back(p[1]);
	//s.push_back(p[2]);
	for (int i = 2; i < n; ++i) {
		// while there is a convex angle
		while ((int)s.size() >= 2 && zcrossprod2(s[(int)s.size() - 2], s[(int)s.size() - 1], p[i]) < 0) {
			s.pop_back();
		}
		s.push_back(p[i]);
	}
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
	sort(grazingSpots.begin(), grazingSpots.end(), TupleCompare<1>());

	vector<tuple<double, double>> s;

	grahamScan(grazingSpots, s);

	double total = 0;
	int sSize = (int)s.size();
	for (int i = 1; i < sSize; ++i) {
		total += sqrt((get<0>(s[i]) - get<0>(s[i - 1])) * (get<0>(s[i]) - get<0>(s[i - 1])) + (get<1>(s[i]) - get<1>(s[i - 1])) * (get<1>(s[i]) - get<1>(s[i - 1])));
	}
	total += sqrt((get<0>(s[0]) - get<0>(s[sSize - 1])) * (get<0>(s[0]) - get<0>(s[sSize - 1])) + (get<1>(s[0]) - get<1>(s[sSize - 1])) * (get<1>(s[0]) - get<1>(s[sSize - 1])));
	
	//int wholeDigits = count_digits(total);
	fout << fixed << setprecision(2) << total << endl;
	return 0;
}