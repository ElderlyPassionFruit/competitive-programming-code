#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];
bool used[MAXN];
int sz[MAXN];
int ans[MAXN];
int centr;

void dfsCentr(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (used[i]) continue;
		if (i == p) continue;
		dfsCentr(i, v, size);
		mx = max(mx, sz[i]);
		sz[v] += sz[i];
	}
	mx = max(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

void solve(int v, int size, int h) {
	dfsCentr(v, -1, size);
	v = centr;
	used[v] = true;
	ans[v] = h++;
	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		solve(i, fsz, h);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	solve(0, n, 0);
	for (int i = 0; i < n; i++) {
		char fans = 'A' + ans[i];
		cout << fans << " ";
	}
	cout << endl;
	return 0;
}