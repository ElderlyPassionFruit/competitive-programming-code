#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

const int MAXN = 1e5 + 10;
int tree[MAXN];
int n;
int get(int r) {
	int ans = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
		ans += tree[r];
	return ans;
}

int get(int l, int r) {
	return get(r) - get(l - 1);
}

void upd(int pos, int val) {
	for (; pos < n; pos |= pos + 1)
	tree[pos] += val;
}

ll k;
vector<pt> a;

struct event{
	int x, y, type;
	event() {}
	event(int _x, int _y, int _type) {
		x = _x, y = _y, type = _type;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

vector<int> coord_y;

bool check(int dist) {
	vector<event> have;
	have.reserve(2 * a.size());
	for (auto i : a) {
		have.push_back(event(i.x, i.y, 1));
		have.push_back(event(i.x + dist + 1, i.y, -1));
	}
	sort(all(have));
	ll ans = 0;
	for (auto [pos, y, type] : have) {
		if (type == -1) {
			upd(y, -1);
		} else {
			int l = lower_bound(all(coord_y), coord_y[y] - dist) - coord_y.begin();
			int r = --upper_bound(all(coord_y), coord_y[y] + dist) - coord_y.begin();
			ans += get(l, r);
			upd(y, 1);
		}
	}
	return ans >= k;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a) {
		int x, y;
		cin >> x >> y;
		i = pt(x + y, x - y);
		coord_y.push_back(x - y);
	}
	sort(all(coord_y));
	coord_y.resize(unique(all(coord_y)) - coord_y.begin());
	for (auto &i : a) {
		i.y = lower_bound(all(coord_y), i.y) - coord_y.begin();
	}
	int l = 0, r = 4e8 + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	cout << r << "\n";
	return 0;
}