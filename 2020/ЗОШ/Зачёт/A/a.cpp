#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll w, h, l, v, n;
	cin >> w >> h >> l >> v >> n;
	ll x = w * h * l;
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		sum += x;
	}
	if (sum + v <= x) {
		cout << 0;
		return 0;
	}
	if (sum >= x) {
		cout << v << endl;
		return 0;
	}
	cout << v - (x - sum) << endl;
	return 0;
}