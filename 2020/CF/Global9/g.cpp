#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int n;

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
}

int h[MAXN];

void dfs(int v, int p) {
	for (auto i : g[v]) {
		if (i == p) continue;
		h[i] = h[v] + 1;
		dfs(i, v); 
	}
} 
 	
int ans;

void run() {
	dfs(0, -1);
	int pos = max_element(h, h + n) - h;
	dfs(pos, -1);
	int npos = max_element(h, h + n) - h;
	ans = h[npos] - h[pos];
	bool ok = false;
	for (int v = 0; v < n; v++) {
		int cnt = 0;
		for (auto i : g[v]) {
			if (g[i].size() > 1) {
				cnt++;
			} 
		}
		if (cnt <= 1) {
			ok = true;
		}
	}
	if (!ok) ans++;
}

void write() {
	cout << ans - 2 << endl;
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