#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

#define int ll

const ld EPS = 1e-9;

struct point{
	ld x, y;
};

struct line{
	ld k, b;
};

ld cross(line a, line b) {
	return (b.b - a.b) / (a.k - b.k);
}

ld eval(line a, int x) {
	return a.k * x + a.b;
}

struct cht{
	vector<line> l;
	vector<ld> p;

	void add(line x) {
		while (!p.empty() && (p.back() >= cross(l.back(), x) || abs(p.back() - cross(l.back(), x)) < EPS))
			l.pop_back(), p.pop_back();
		l.push_back(x);
		if (l.size() >= 2) {
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
		}
	}

	ld get(int x) {
		int pos = lower_bound(all(p), x) - p.begin();
		return eval(l[pos], x);
	}
};

cht up, down;
int n;
ld UP, DOWN, LEFT, RIGHT;
vector<point> a;
vector<line> fup, fdown;

void make(point p, point i) {
	if (p.x == i.x) {
		ld c = (p.y + i.y) / 2;
		if (i.y - p.y < 0) {
			DOWN = max(DOWN, c);
		}
		else {
			UP = min(UP, c);
		}
	}
	else if (p.y == i.y) {
		ld c = (p.x + i.x) / 2;
		if (i.x - p.x < 0) {
			LEFT = max(LEFT, c);
		}
		else {
			RIGHT = min(RIGHT, c);
		}	
	}
	else {
		line l;
		l.k = -(i.x - p.x) / (i.y - p.y);
		l.b = -(p.x * p.x + p.y * p.y - i.x * i.x - i.y * i.y) / (2*(i.y - p.y));
		if (i.y - p.y > 0) {
			fup.push_back(l);
		}
		else {
			fdown.push_back(l);
		}
	}
}

void del(vector<line> & l) {
	if (l.empty())
		return;
	vector<line> ans;
	ans.push_back(l[0]);
	for (int i = 1; i <(int) l.size(); i++) {
		if (abs(l[i].k - ans.back().k) > EPS)
			ans.push_back(l[i]);
	}
	l = ans;
}

void build() {
	for (int i = 1; i < n; i++)
		make(a[0], a[i]);
	sort(fup.begin(), fup.end(), [&] (line l, line m) {return tie(m.k, l.b) < tie(l.k, m.b);}); 
	del(fup);
	sort(fdown.begin(), fdown.end(), [&] (line l, line m) {return tie(l.k, m.b) < tie(m.k, l.b);}); 
	del(fdown);
	for (auto i : fup)
		up.add(i);
	for (auto i : fdown)
		down.add(i);
}

bool check(ld x) {
	return abs(x - (ll)x) < EPS;
}

int Ceil(ld x) {
	return (check(x) ? x : ceil(x));
}

int Floor(ld x) {
	return (check(x) ? x : floor(x));
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> RIGHT >> UP >> n;
	DOWN = LEFT = 0;
	a.resize(n);
	for (auto &i : a)
		cin >> i.x >> i.y;
	build();
	ll ans = 0;
	for (int i = ceil(LEFT); i <= floor(RIGHT); i++) {
		ll u = Floor(UP);
		if (!up.l.empty()) u = min(Floor(UP), Floor(up.get(i)));
		ll d = Ceil(DOWN);
		if (!down.l.empty()) d = max(Ceil(DOWN), Ceil(down.get(i)));
		if (u >= d)
			ans += u - d + 1;
	}
	cout << ans << endl;
	return 0;
}