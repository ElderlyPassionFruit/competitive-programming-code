#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	ll x, y;
	point() {}
	point(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ll operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

ll operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

ll sq(ld x) {
	return x * x;
}

#define vec point

ld dist(vec a) {
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

int n;
vector<point> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.x >> i.y;
}

const ld INF = 1e18;
vector<ld> ans;

bool check(point a, point b, point x) {
	if (a == b) return a == x;
	vec v1, v2;
	v1 = x - a, v2 = b - a;
	if ((v1 ^ v2) != 0) return false;
	if (v1 * v2 < 0) return false;
	v1 = x - b, v2 = a - b;
	if (v1 * v2 < 0) return false;
	return true;
}

bool check_angle(point a, point b, point c, point x) {
	vec v1 = b - a;
	vec v2 = c - a;
	if ((v1 ^ v2) == 0) return check(a, b, x) || check(a, c, x) || check(b, c, x);
	vec v3 = x - a;
	if ((v1 ^ v2) < 0) swap(v1, v2);
	return (v1 ^ v3) >= 0 && (v3 ^ v2) >= 0;
}

bool check(point a, point b, point c, point x) {
	return check_angle(a, b, c, x) && check_angle(b, c, a, x) && check_angle(c, a, b, x);
}

void solve(int ind) {
	vector<point> have;
	for (auto i : a) {
		if (tie(a[ind].x, a[ind].y) <= tie(i.x, i.y)) {
			have.push_back(i);
		}
	}
	p0 = a[ind];
	sort(all(have), cmp);
	int n = have.size();

	vector<vector<ld>> dp(n, vector<ld> (n + 1, INF));

	dp[0][1] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			int cnt1 = 0, cnt2 = 0;
			for (int x = 0; x < n; x++) {
				cnt1 += check(have[j], have[0], have[x]);
				if (j != 0)
				cnt2 += check(have[i], have[j], have[0], have[x]);
				else
				cnt2 += check(have[i], have[0], have[x]);
			}
		
			for (int k = 1; k <= n; k++) {
				if (dp[j][k] == INF) continue;
				int nxt = k - cnt1 + cnt2;
				chkmin(dp[i][nxt], dp[j][k] - dist(have[0], have[j]) + dist(have[i], have[j]) + dist(have[0], have[i]));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			chkmin(ans[j - 1], dp[i][j]);			
		}
	}
}

void run() {
	ans.resize(n, INF);
	ans[0] = 0;
	for (int i = 0; i < n; i++) {
		solve(i);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
	}
}

signed main() {
	cout.precision(10);
	cout.setf(ios::fixed);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}