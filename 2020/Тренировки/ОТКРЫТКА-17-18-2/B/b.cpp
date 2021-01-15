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
	point(ll _x, ll _y) {
		x = _x, y = _y;
	} 
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

ll operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct line{
	ll a, b, c;
	line() {}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

bool check_cross(line l, line m) {
	ll d = l.b * m.a - l.a * m.b;
	if (d == 0) return false;
	ll dx = l.c * m.b - l.b * m.c;
	ll dy = l.a * m.c - l.c * m.a;
	return dx % d == 0 && dy % d == 0;
}

point cross(line l, line m) {
	ll d = l.b * m.a - l.a * m.b;
	ll dx = l.c * m.b - l.b * m.c;
	ll dy = l.a * m.c - l.c * m.a;
	return {dx / d, dy / d};
}

int n;
vector<point> a;
set<point> fa;

void read() {
	cin >> n;
	n *= 2;
	a.resize(n);
	for (auto &i : a){
		cin >> i.x >> i.y;
		fa.insert(i);
	}
}

mt19937 rnd(time(0));
set<point> have;

void solve(int ind1, int ind2, int ind3, int ind4) {
	if (ind2 == ind4 || ind3 == ind4) return;
	line l = line(a[ind1], a[ind2]);
	line m = line(a[ind3], a[ind4]);
	if (!check_cross(l, m)) return;
	point fans = cross(l, m);
	if (have.count(fans)) return;
	have.insert(fans);
	if (fa.count(fans)) return;
	if (max(abs(fans.x), abs(fans.y)) > 1e6) return;
	
	vector<bool> used(n);
	
	for (int i = 0; i < n / 2; i++) {
		int ind = rnd() % n;
		while (used[ind]) ind = rnd() % n;
		bool flag = false;
		for (int j = 0; j < n; j++) {
			if (j == ind) continue;
			if (used[j] && ((a[ind] - fans) ^ (a[j] - fans)) == 0) return;
			if (used[j]) continue;
			if ((a[ind] - fans) ^ (a[j] - fans)) continue;
			used[j] = true;
			used[ind] = true;
			flag = true;
			break;
 		}
 		if (!flag) return;
	}

	cout << "Yes\n";
	cout << fans.x << " " << fans.y << "\n";
	exit(0); 
}

void run() {
	shuffle(all(a), rnd);
	int ind1 = 0;
	for (int ind2 = 1; ind2 < n; ind2++) {
		int ind3 = 1;
		while (ind3 == ind1 || ind3 == ind2) ind3++;
		for (int ind4 = 1; ind4 < n; ind4++) {
			solve(ind1, ind2, ind3, ind4);
		}
	}
}

void write() {
	cout << "No" << endl;
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