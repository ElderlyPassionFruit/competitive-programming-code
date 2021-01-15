#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
int n, k, t;
int p[MAXN];
ll ans;

void add(int x) {
	ans += (ll)(t / k) * (k / x);
	ans += (ll)(t % k) / x;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k >> t;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	ans = 0;
	for (int i = 0; i < n; i++) {
		add(p[i]);
	}
	cout << ans << endl;
	return 0;
}