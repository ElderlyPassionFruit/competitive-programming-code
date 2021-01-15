#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 2e5 + 10;
int n;
vector<int> g[MAXN];
int w[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(w[v]);
		g[v].push_back(w[u]);
	}
	ld ans = 0;
	for (int i = 0; i < n; i++) {
		if(g[i].empty()) continue;
		sort(all(g[i]));
		reverse(all(g[i]));
		int sum = w[i];
		int cnt = 1;
		for (auto j : g[i]) {
			sum += j;
			cnt++;
			ans = max(ans, (ld) sum / cnt);
		}
	}
	cout << ans << endl;
	return 0;
}