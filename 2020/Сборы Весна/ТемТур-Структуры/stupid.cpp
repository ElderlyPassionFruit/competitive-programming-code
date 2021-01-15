#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 300 + 10;
vector<int> g[MAXN];
int n, q;
int a[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
		g[i].push_back(p);
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int tin[MAXN], tout[MAXN], timer = 0;

void dfs_tin(int v, int p) {
	tin[v] = timer++;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_tin(i, v);
		}
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int len[MAXN];
void dfs(int v, int p) {
	len[v] = 0;
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v);
			chkmax(len[v], len[i] + 1);
		}
	}
}

bool used[MAXN];

void run() {
	dfs_tin(0, 0);
	for (int i = 0; i < n; i++)
		used[i] = true;
	while (q--) {
		char type;
		cin >> type;
		if (type == '?') {
			int v, t;
			cin >> v >> t;
			v--;
			dfs(v, -1);
			int ans = 0;
			for (int i = 0; i < n; i++) {
				if (is_upper(i, v) && used[i]) {
					chkmax(ans, a[i] + len[i] * t);
				}
			}
			cout << ans << "\n";
		} else if (type == '+') {
			int v;
			cin >> v;
			v--;
			used[v] = true;
		} else {
			int v;
			cin >> v;
			v--;
			used[v] = false;
		}
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}