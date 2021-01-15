#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	ld x, y;
	pt() {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

pt operator-(const pt & a, const pt & b) {
	return pt(a.x - b.x, a.y - b.y);
}

ld sq(ld x) {
	return x * x;
}

ld dist(pt a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(pt a, pt b) {
	return dist(a - b);
}

pt s, t;
int n;
vector<pair<pt, ld> > a;

void read() {
	cin >> s.x >> s.y >> t.x >> t.y;
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.first.x >> i.first.y >> i.second;
	}
}

ld ans = 1e18;

void run() {
	for (int i = 0; i < n; i++) {
		pt p = a[i].first;
		ld T = a[i].second;
		chkmin(ans, dist(s, p) + dist(p, t) + T);
	}
}

void write() {
	cout.precision(20);
	cout << ans << endl;
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