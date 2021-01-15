#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
const ll INF = 1e18;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int x, y;
	cin >> x >> y;
	int n;
	cin >> n;
	ll min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
	for (int i = 0; i < n; i++) {
		ll x, y;
		cin >> x >> y;
		min_x = min(min_x, x + y);
		max_x = max(max_x, x + y);
		min_y = min(min_y, x - y);
		max_y = max(max_y, x - y);
	}


	ll dist = INF, ind = 0;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		ll x, y;
		cin >> x >> y;
		ll x1 = x + y;
		ll y1 = x - y;
		ll d = 0;
		d = max(d, x1 - min_x);
		d = max(d, max_x - x1);
		d = max(d, y1 - min_y);
		d = max(d, max_y - y1);
		if (d < dist) {
			dist = d;
			ind = i + 1;
		}
	}
	cout << dist << endl;
	cout << ind << endl;
	return 0;
}