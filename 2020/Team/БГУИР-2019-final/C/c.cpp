#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

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

ll operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

ll sq(ll x) {
	return x * x;
}

ll dist(point a) {
	return sq(a.x) + sq(a.y);
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
	if (n == 0) return {};
	for (int i = 0; i < n; i++) {
		if (tie(p[i].x, p[i].y) < tie(p[0].x, p[0].y)) {
			swap(p[i], p[0]);
		}
	}
	p0 = p[0];
	sort(p.begin() + 1, p.end(), cmp);
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
	return hull;
}

ll area(vector<point> p) {
	ll ans = 0;
	int n = p.size();
	for (int i = 0; i < n; i++) {
		ans += p[i] ^ p[(i + 1) % n];
	}
	return abs(ans);
}

const int INF = 1e4 + 228;

ll get(vector<point> & p, ll x) {
	vector<point> L, R;
	for (auto i : p) {
		if (i.x <= x)
			L.push_back(i);
		else
			R.push_back(i);
	}
	L = convex_hull(L);
	R = convex_hull(R);
	return area(L) - area(R);
}

pair<ll, ll> my_lower_bound(ll need, vector<point> p) {
	vector<int> have_x;
	have_x.push_back(-INF);
	have_x.push_back(INF);
	for (auto i : p)
		have_x.push_back(i.x);
	sort(all(have_x));
	int l = 0, r = have_x.size();
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (get(p, have_x[mid]) <= need)
			l = mid;
		else
			r = mid;
	}
	ll have;
	have = get(p, have_x[l]);
	pair<ll, ll> ans = make_pair(abs(need - have), have);
	for (int i = max(0, l - 5); i < min((int)have_x.size(), l + 5); i++) {
		have = get(p, have_x[i]);
		ans = min(ans, make_pair(abs(need - have), have));
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll n, s;
	cin >> n >> s;
	s *= 2;
	vector<point> p(n);
	for (auto &i : p)
		cin >> i.x >> i.y;
	auto ans = min(my_lower_bound(s, p), my_lower_bound(-s, p));
	ans.second = abs(ans.second);
	cout << ans.second / 2;
	if (ans.second & 1)
		cout << ".5";
	cout << endl;
	return 0;
}