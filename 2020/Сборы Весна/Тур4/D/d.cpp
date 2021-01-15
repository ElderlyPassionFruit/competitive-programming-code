#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define vec point

int sign(ll a) {
	if (a == 0) return 0;
	if (a > 0) return 1;
	return -1;
}

struct point{
	int x, y;
	point() {}
	point(int _x, int _y) {
		x = _x, y = _y;
	}
};

struct segm{
	vec l, r;
	segm() {}
	segm(vec _l, vec _r) {
		l = _l, r = _r;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

ll operator^(const point & a, const point & b) {
	return (ll)a.x * b.y - (ll)a.y * b.x;
}

ll operator*(const point & a, const point & b) {
	return (ll)a.x * b.x + (ll)a.y * b.y;
}

ll sq(ll x) {
	return x * x;
}

ll dist(point a) {
	return sq(a.x) + sq(a.y);
}

int half(vec a) {
	return a.y > 0 || (a.y == 0 && a.x >= 0);
}  

bool operator<(const point & a, const point & b) {
	if (half(a) != half(b)) {
		return half(a);
	}
	return (a ^ b) > 0; 
}

bool operator<(const segm & a, const segm & b) {
	bool flag1 = half(a.l) >= half(a.r);
	bool flag2 = half(b.l) >= half(b.r);
	if (flag1 != flag2) {
		return flag1;
	}
	return a.r < b.r;	
}

int n, q;
vector<point> p;
vector<point> a;

void read() {
	cin >> n >> q;
	p.resize(n);
	for (auto &i : p)
		cin >> i.x >> i.y;
	a.resize(q);
	for (auto &i : a)
		cin >> i.x >> i.y;
}

bool is_left(int ind, point a) {
	vec v1 = p[ind] - a;
	vec v2 = p[(ind + 1) % n] - a;
	if (sign(v1 ^ v2) == 0) {
		return dist(v1) > dist(v2);
	}
	return sign(v1 ^ v2) == 1;
}

pair<int, int> get_left(point a) {
	int l, r;
	l = 0, r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (sign((p[0] - a) ^ (p[mid] - a)) >= 0) {
			l = mid;
		} else {
			r = mid;
		}
	}

	int centr;
	centr = l;
	int ans1, ans2;
	if (centr == 0) {
		ans1 = 0;
	} else {
		l = 0, r = centr + 1;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (is_left(mid, a)) {
				l = mid;
			} else {
				r = mid;
			}
		}
		ans1 = r % n;
	}

	l = centr;
	r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (is_left(mid, a)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	ans2 = r % n;
	return {ans1, ans2};
}

pair<int, int> get_right(point a) {
	int l, r;
	l = 0, r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (sign((p[0] - a) ^ (p[mid] - a)) < 0) {
			l = mid;
		} else {
			r = mid;
		}
	}

	int centr;
	centr = r;
	int ans1, ans2;
	
	l = 0, r = centr;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (is_left(mid, a)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	ans2 = r % n;
	
	l = centr - 1;
	r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (is_left(mid, a)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	ans1 = r % n;
	return {ans1, ans2};
}

segm get_tangent(point a) {
	segm ans;
	pair<int, int> fans;
	if (is_left(0, a)) {
		fans = get_left(a);
	} else {
		fans = get_right(a);
	}
	fans.first %= n;
	fans.second %= n;
	swap(fans.first, fans.second);
	ans.l = p[fans.first] - a;
	ans.l = vec(-ans.l.x, -ans.l.y);
	ans.r = p[fans.second] - a;
	swap(ans.l, ans.r);
	return ans;
}

vector<segm> have;

void build() {	
	for (auto i : a) {
		have.push_back(get_tangent(i));
	}
}

ll ans;

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int _n) {
		n = _n;
		tree.assign(n, 0);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos |= pos + 1)
			tree[pos] += val;
	} 
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
};

void calc(vector<segm> have) {
	vector<point> coord;
	for (auto i : have)
		coord.push_back(i.r);
	fenvik tree(coord.size());
	int add = 0;
	for (int i = 0; i < (int)have.size(); i++) {
		int pos = lower_bound(all(coord), have[i].l) - coord.begin();
		ans += tree.get(pos, i);
		add += tree.get(pos, i);
		tree.upd(i, 1);
	}
}

void calc(vector<segm> L, vector<segm> R) {
	vector<point> have;
	for (auto i : L) {
		if (half(i.l)) {
			have.push_back(i.l);
		} 
		if (!half(i.r)) {
			have.push_back(i.r);
		}
	}
	sort(all(have));
	for (auto i : R) {
		int pos1 = upper_bound(all(have), i.r) - have.begin();
		int pos2 = lower_bound(all(have), i.l) - have.begin();
		int add = have.size() - (pos2 - pos1);
		ans += add;
	}
}

void calc() {
	sort(all(have));
	vector<segm> L, R;
	for (auto i : have) {
		bool flag = half(i.l) >= half(i.r);
		if (flag) {
			L.push_back(i);
		} else {
			R.push_back(i);
		}
	}

	calc(L, R);
	calc(L);
	for (auto &i : R) {
		i.l = vec(-i.l.x, -i.l.y);
		i.r = vec(-i.r.x, -i.r.y);
	}
	calc(R);
}

void run() {
	build();
	calc();
}

void write() {
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