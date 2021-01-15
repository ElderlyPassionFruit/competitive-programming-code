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
	point(int a, int b) {
		x = a, y = b;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int sign(int x) {
	if (x == 0) return x;
	return x / abs(x);
}

bool check(int l1, int r1, int l2, int r2) {
	if (l1 > r1) swap(l1, r1);
	if (l2 > r2) swap(l2, r2);
	return min(r1, r2) >= max(l1, l2);
}

#define vec point

bool check(point a, point b, point c, point d) {
	if (!check(a.x, b.x, c.x, d.x)) return false;
	if (!check(a.y, b.y, c.y, d.y)) return false;
	vec v1 = b - a, v2 = c - a, v3 = d - a;
	if (sign(v1 ^ v2) * sign(v1 ^ v3) > 0) return false;
	v1 = d - c, v2 = a - c, v3 = b - c;
	if (sign(v1 ^ v2) * sign(v1 ^ v3) > 0) return false;
	return true;
}

int n = 4;
vector<point> g;
point a, b;
void read() {
	g.resize(n);
	for (auto &i : g)
		cin >> i.x >> i.y;
	a = g[0];
	b = g[1];
}

bool check(vector<int> have) {
	vector<point> p;
	for (int i = 0; i < have.size(); i++)
		p.push_back(g[have[i]]);
	return !check(p[0], p[1], p[2], p[3]) && !check(p[1], p[2], p[0], p[3]);
}

bool f1, f2;

void recalc(vector<int> have) {
	vector<point> p;
	for (int i = 0; i < have.size(); i++)
		p.push_back(g[have[i]]);
	bool flag = false;
	for (int i = 0; i < have.size(); i++) {
		point a1 = p[i];
		point b1 = p[(i + 1) % 4];
		if (a == a1 && b == b1)
			flag = true;
		if (a == b1 && b == a1)
			flag = true;
	}
	if (flag) f1 = true;
	else f2 = true;
}

void run() {
	vector<int> have = {0, 1, 2, 3};
	f1 = false;
	f2 = false;
	do {
		if (check(have)) {
			recalc(have);
		}
	} while (next_permutation(all(have)));
}

void write() {
	if (f1 && f2) 
		cout << 0 << endl;
	else if (f1)
		cout << 1 << endl;
	else 
		cout << -1 << endl;
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