/*
	Circle intersection
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
#define mp make_pair
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ld eps = 1e-9;
bool eq(ld x, ld y) {
	return fabsl(x - y) < eps;
}
bool ls(ld x, ld y) {
	return x < y && !eq(x, y);
}
bool lseq(ld x, ld y) {
	return x < y || eq(x, y);
}

ld readLD() {
	double x;
	scanf("%lf", &x);
	return x;
}

struct Point {
	ld x, y;

	Point() : x(), y() {}
	Point (ld _x, ld _y) : x(_x), y(_y) {}

	void scan() {
		x = readLD();
		y = readLD();
	}
	void print() {
		printf("%.14lf %.14lf\n", (double)x, (double)y);
	}

	Point operator + (const Point &a) const {
		return Point(x + a.x, y + a.y);
	}
	Point operator - (const Point &a) const {
		return Point(x - a.x, y - a.y);
	}
	Point operator * (const ld &k) const {
		return Point(x * k, y * k);
	}
	Point operator / (const ld &k) const {
		return Point(x / k, y / k);
	}
	ld operator % (const Point &a) const {
		return x * a.x + y * a.y;
	}
	ld operator * (const Point &a) const {
		return x * a.y - y * a.x;
	}
	ld sqrLen() const {
		return *this % *this;
	}
	ld len() const {
		return sqrtl(sqrLen());
	}
	Point norm() const {
		return *this / len();
	}
	Point ort() const {
		return Point(-y, x);
	}

	bool operator == (const Point &a) const {
		return eq(x, a.x) && eq(y, a.y);
	}
};

bool intersectCircles(Point O1, ld R1, Point O2, ld R2, Point &I1, Point &I2) {
	ld L = (O1 - O2).len();
	if (ls(R1 + R2, L) || ls(L, fabsl(R1 - R2)) || eq(L, 0)) return false;
	if (eq(R1 + R2, L) || eq(L, fabsl(R1 - R2))) {
		I1 = I2 = O1 + (O2 - O1).norm() * R1;
		return true;
	}
	ld x = (R1 * R1 - R2 * R2 + L * L) / (2 * L);
	Point H = O1 + (O2 - O1).norm() * x;
	Point a = (O2 - O1).norm().ort();
	I1 = H + a;
	I2 = H - a;
	return true;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	Point O1, O2;
	ld R1, R2;
	O1.scan();
	R1 = readLD();
	O2.scan();
	R2 = readLD();
	Point I1, I2;
	if (O1 == O2 && eq(R1, R2)) {
		printf("infinity\n");
		return 0;
	}
	if (!intersectCircles(O1, R1, O2, R2, I1, I2)) {
		printf("0\n");
		return 0;
	}
	if (I1 == I2) {
		printf("1\n");
		I1.print();
	} else {
		printf("2\n");
		I1.print();
		I2.print();
	}

	return 0;
}
