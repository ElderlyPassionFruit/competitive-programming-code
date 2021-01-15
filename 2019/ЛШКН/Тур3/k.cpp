#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];
int col[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> col[i];
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

int colors[MAXN], cnt_ans;

void add(int c, int cnt) {
	if (colors[c] == 0)
		cnt_ans++;
	colors[c] += cnt;
}

void del(int c, int cnt) {
	if (colors[c] == cnt) 
		cnt_ans--;
	colors[c] -= cnt;
}

int get() {
	return cnt_ans;
}

void make() {
	for (int i = 0; i < MAXN; i++)
		colors[i] = 0;
	cnt_ans = 0;
	for (int i = 0; i < n; i++)
		add(col[i], 1);
}

bool dfs(int v, int p) {
	bool flag = false;
	for (auto i : g[v]) {
		if (i != p) {
			flag |= dfs(i, v);
		}
	}
	if (flag)
		return true;

	del(col[v], 1);
	for (auto i : g[v]) {
		if (i != p) {
			del(col[i], sz[i]);
		}
	}

	if (get() <= 1) {
		cout << "YES" << endl;
		cout << v + 1 << endl;
		exit(0);
	}

	add(col[v], 1);
	for (auto i : g[v]) {
		if (i != p) {
			add(col[i], sz[i]);
		}
	}

	for (auto i : g[v]) {
		if (i != p) {
			if (col[i] != col[v])
				return true;
		}
	}
	return false;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	dfs_sz(0, -1);
	/*cout << "sz = " << endl;
	for (int i = 0; i < n; i++)
		cout << sz[i] << " ";
	cout << endl;*/
	make();
	dfs(0, -1);
	cout << "NO" << endl;
	return 0;
}