#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define ld long double
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y, ind;
	point() {}
	point(int a, int b) {
		x = a, y = b;
	}
};

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

ld sq(ld x) {
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

vector<point> convex_hull(vector<point> g){
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (tie(g[i].x, g[i].y) < tie(g[0].x, g[0].y))
			swap(g[i], g[0]);
	}
	p0 = g[0];
	sort(g.begin() + 1, g.end(), cmp);
	vector<point> hull;
	for (int i = 0; i < n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last] - hull[last - 1];
			vec v2 = g[i] - hull[last];
			if ((v1 ^ v2) > 0) break;
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	return hull;
}

int n;
vector<point> g;

void read() {
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> g[i].x >> g[i].y;
		g[i].ind = i;
	}
	g = convex_hull(g);
	n = g.size();
}

bool check(point a, point b, point x) {
	if (a == x) return true;
	if (b == x) return true;
	vec v1 = a - x, v2 = b - x;
	if ((v1 * v2) > 0) return false;
	v1 = x - a, v2 = b - a;
	if ((v1 ^ v2) != 0) return false;
	return true;
}

bool check(point x) {
	if (n == 1) return (x == g[0]);
	if (n == 2) return check(g[0], g[1], x);
	vec v1 = x - g[0], v2 = g[1] - g[0];
	if ((v2 ^ v1) < 0) return false;
	v2 = g[n - 1] - g[0];
	if ((v2 ^ v1) > 0) return false;
	return true;
}

bool check(vector<point> g, point a) {
	int n = g.size();
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		point x = g[i];
		point y = g[(i + 1) % n];
		if (check(x, y, a)) return true;
		x = x - a;
		y = y - a;
		ans += atan2(x ^ y, x * y);
	}
	return abs(ans) > 3;
}

struct fans{
	bool flag;
	vector<int> ans;
	fans() {}
};

vector<fans> ans;

fans solve1(point i) {
	fans ans;
	if (i == g[0]) {
		ans.flag = true;
		ans.ans = {g[0].ind};
	}
	else {
		ans.flag = false;
	}
	return ans;
}

fans solve2(point i) {
	fans ans;
	if (check(g[0], g[1], i)) {
		ans.flag = true;
		ans.ans = {g[0].ind, g[1].ind};
	}
	else {
		ans.flag = false;
	}
	return ans;
}

fans stupid_solve(point a) {
	if (n == 1) return solve1(a);
	if (n == 2) return solve2(a);

	for (int i = 2; i < n; i++) {
		if (check({g[0], g[i - 1], g[i]}, a)) {
			fans ans;
			ans.flag = true;
			ans.ans = {g[0].ind, g[i - 1].ind, g[i].ind};
			return ans;
		}
	}
	fans ans;
	ans.flag = false;
	return ans;
}

void run() {
	int m;
	cin >> m;
	ans.resize(m);
	vector<point> q(m);
	for (int i = 0; i < m; i++) {
		cin >> q[i].x >> q[i].y;
		q[i].ind = i;
		if (n <= 2)
			ans[i] = stupid_solve(q[i]);
	}
	if (n <= 2) return;
	
	vector<point> good;
	for (auto i : q) {
		if (check(i)) {
			good.push_back(i);
		}
		else {
			ans[i.ind].flag = false;
		}
	}
	//return;
	sort(all(good), cmp);
	
	//for (auto i : good) {
	//	ans[i.ind] = stupid_solve(i);
	//}
	//return;

	int pos = 0;
	for (int i = 2; i < n; i++) {
		while (pos < good.size() && ((good[pos] - p0) ^ (g[i] - p0)) >= 0) {
			if (check({g[0], g[i], g[i - 1]}, good[pos])) {
				ans[good[pos].ind].flag = true;
				ans[good[pos].ind].ans = {g[0].ind, g[i].ind, g[i - 1].ind};
			}
			else {
				ans[good[pos].ind].flag = false;
			}
			pos++;
		}
	}
}
 
void write() {
	for (auto i : ans) {
		if (i.flag) {
			cout << i.ans.size() << " ";
			for (auto j : i.ans)
				cout << j + 1 << " ";
			cout << "\n";
		}
		else {
			cout << -1 << "\n";
		}
	}
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