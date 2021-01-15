#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> deg(n, 0);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		deg[u]++;
		deg[v]++;
	}
	int ans = 0;
	for (auto i : deg) {
		assert(i != 0);
		ans += i == 1;
	}
	ans = (ans + 1) / 2;
	cout << ans << endl;
	return 0;
}