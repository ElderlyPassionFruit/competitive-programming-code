#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n;
bool used[MAXN];
vector<int> path;
int s, f;
bool flag = false;

void dfs_path(int v, int p) {
	used[v] = true;
	path.push_back(v);
	if (v == f) {
		flag = true;
		return;
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs_path(i, v);
		if (flag)
			return;
	}
	used[v] = false;
	path.pop_back();
}

int h[MAXN];

void dfs_h(int v, int p, int len) {
	h[v] = len++;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_h(i, v, len);
			h[v] = max(h[v], h[i]);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("dwarfs.in", "r", stdin);
	freopen("dwarfs.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin >> s >> f;
	s--;
	f--;
	dfs_path(s, s);
	for (int i = 0; i < n; i++) {
		if (used[i]) {
			dfs_h(i, i, 0);
		}
	}
	/*cout << "path = " << endl;
	for (auto i : path)
		cout << i << " ";
	cout << endl;*/

	vector<int> pref(path.size()), suff(path.size());
	pref[0] = h[path[0]];
	for (int i = 1; i < path.size(); i++)
		pref[i] = max(pref[i - 1], h[path[i]] + i);
	suff[path.size() - 1] = h[path[path.size() - 1]];
	for (int i = path.size() - 2; i >= 0; i--)
		suff[i] = max(suff[i + 1], h[path[i]] + (int)path.size() - 1 - i);

	int ans = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		ans = max(ans, min(pref[i], suff[i + 1]));
	}
	cout << ans + 1 << endl;
	return 0;
}













