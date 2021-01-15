#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ll operator^(const point & a, const point & b) {
	return (ll) a.x * b.y - a.y * b.x;
}

ll sq(ll x) {
	return x * x;
}

ld dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

ld dist(point a, point b) {
	return dist(a - b);
}

point p0;

bool cmp(point a, point b) {
	a = a - p0;
	b = b - p0;
	if ((a ^ b) == 0) {
		return dist(a) < dist(b);
	}
	return (a ^ b) > 0;
}

#define vec point

vector<point> convex_hull(vector<point> p) {
	int n = p.size();
	for (int i = 1; i < n; i++) {
		if (tie(p[i].x, p[i].y) < tie(p[0].x, p[0].y)) {
			swap(p[0], p[i]);
		}
	}
	p0 = p[0];
	sort(p.begin() + 1, p.end(), cmp);
	//p.push_back(p0);
	vector<point> hull;
	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = p[i] - hull[last];
			if ((v1 ^ v2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(p[i]);
	}
	//hull.pop_back();
	return hull;
}

ld get_per(vector<point> p) {
	ld ans = 0;
	int n = p.size();
	for (int i = 0; i < n; i++) {
		ans += dist(p[i], p[(i + 1) % n]);
	}
	return ans;
}

int n;
vector<point> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.x >> i.y;
}

ld get(int mask) {
	vector<point> p;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			p.push_back(a[i]);
		}
	}
	p = convex_hull(p);
	return get_per(p);
}

int cnt(int n) {
	int ans = 0;
	while (n) {
		ans += n % 2;
		n /= 2;
	}
	return ans;
}

vector<ld> ans;

void wr_mask(int mask) {
	for (int i = 0; i < n; i++) {
		cout << mask % 2 << " ";
		mask /= 2;
	}
	cout << endl;
}

void run() {
	ans.resize(n + 1, 1e18);
	for (int mask = 1; mask < (1 << n); mask++) {
		chkmin(ans[cnt(mask)], get(mask));
		if (0 && cnt(mask) == 12 && abs(get(mask) - 22.8518911625) < 1e-6) {
			//cout << mask << endl;
			wr_mask(mask);
		}
	}
	ans.erase(ans.begin());
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.precision(10);
	cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}
