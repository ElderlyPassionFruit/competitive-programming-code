#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
const int INF = 1e18;
map <int, vector<int> > points;
	int n, m, k;
int rb, cb;

int get(int x) {
	return x * (x + 1) / 2;
}

int get_x(int l, int r) {
	return get(r) - get(l - 1);
}

int get(int y1, int y2) {
	if (y1 > y2) return 0;
	y1 -= cb;
	y2 -= cb;
	y1 = abs(y1);
	y2 = abs(y2);
	if (y1 > y2) swap(y1, y2);
	return get_x(y1, y2);
} 

int get(int x, int y1, int y2) {
	if (x > n || x < 1) return INF;
	if (y2 > n || y1 < 1) return INF;
	auto it = lower_bound(all(points[x]), y1);
	if (it != points[x].end() && *it <= y2) return INF;
	int ans = 0;
	ans += abs(x - rb) * (y2 - y1 + 1);
	if (y1 >= cb || y2 <= cb) ans += get(y1, y2);
	else ans += get(y1, cb) + get(cb, y2);
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	//cout.precision(20);
	freopen("cinema.in","r",stdin);
	freopen("cinema.out","w",stdout);
	cin >> n >> m >> k;
	set<int> have;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		have.insert(x);
		points[x].push_back(y);
	}
	cin >> rb >> cb;
	int ans = INF;
	for (auto i : have) {
		sort(points[i].begin(), points[i].end());
	}

	for (auto i : points) {
		for (auto j : i.second) {
			ans = min(ans, get(i.first, j + 1, j + 1 + k - 1));
			ans = min(ans, get(i.first, j - k, j - 1));
		}
	}

	for (int i = 0; i <= m; i++) {
		int x = cb - k/2;
		x = max(x, 1LL);
		ans = min(ans, get(rb + i, x, x + k - 1));
		ans = min(ans, get(rb - i, x, x + k - 1));
	}
	if (ans == INF)
		cout << -1;
	else
		cout << ans;
	return 0;
}