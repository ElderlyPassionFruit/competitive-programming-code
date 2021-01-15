#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;

int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
}

int sz[MAXN];

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

int ans[MAXN];

void dfs_calc(int v, int p) {
	ans[v] = ans[p] + sz[p] - sz[v] + 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_calc(i, v);
		}
	}
}

void run() {
	dfs_sz(0, 0);
	ans[0] = 2;
	for (auto i : g[0]) {
		dfs_calc(i, 0);
	}
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << ans[i] / 2;
		if (ans[i] % 2 == 1)
			cout << ".5";
		cout << " "; 
	}
	cout << endl;
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