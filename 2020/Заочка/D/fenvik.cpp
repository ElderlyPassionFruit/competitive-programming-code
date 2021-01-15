#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;

int n, k;
vector<int> g[MAXN];
vector<int> l[MAXN];
vector<int> r[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		l[i].resize(n);
		r[i].resize(n);
		for (int j = 0; j < n; j++) {
			cin >> l[i][j] >> r[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans = MAXN;

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int sz) {
		n = sz;
		tree.assign(n, MAXN);
	}

	int get(int r) {
		int ans = MAXN;
		for (int i = 0; i <= r; i++) {
			chkmin(ans, tree[i]);
		}
	}

	void upd(int pos, int val) {
		chkmax(tree[pos], val);
	}
};



void dfs_sz(int v, int p) {

}

void run() {
	dfs(0, 0);
}

void write() {
	if (ans == MAXN)
		cout << -1 << endl;
	else
		cout << ans << endl;
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