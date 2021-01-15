#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	ll x, y;
	point() {}
	point(ll a, ll b) {
		x = a, y = b; 
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ld sq(ld x) {
	return x * x;
}

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

int n, m;
int r, k;
vector<vector<int> > p;

void read() {
	cin >> n >> m >> r >> k;
	p.resize()
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}