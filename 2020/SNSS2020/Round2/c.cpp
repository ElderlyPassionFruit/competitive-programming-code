#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct Point{
	int x, y;
	Point() {

	}
	Point(int _x, int _y) {
		x = _x, y = _y;
	}
};

ld sq(ld x) {
	return x * x;
}

ld dist(Point a, Point b) {
	return sqrt(sq(a.x - b.x) + sq(a.y - b.y));
}

const int N = 15, M = 210;
int n, m;
Point a[N];
Point q[M];

void read() {
	cin >> n >> m;
	
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}