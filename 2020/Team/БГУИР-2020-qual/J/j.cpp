#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 5e5 + 10;
int n;
vector<int> g[MAXN];
int p[MAXN];

void solve() {
	cin >> n ;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		g[i].clear();
	}
	for (int i = 0; i < n; i++) {
		if (p[i] == -1) continue;
		g[i].push_back(p[i]);
	}

} 

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}