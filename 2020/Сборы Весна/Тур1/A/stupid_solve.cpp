#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 20;
int n, k;
vector<int> g[MAXN];
int c[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++)
		cin >> c[i];
}

int nc[MAXN];
bool used[MAXN];

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i]) continue;
		if (nc[i]) continue;
		dfs(i);
	}
}

bool check(int mask) {
	for (int i = 0; i < n; i++) {
		used[i] = false;
		if ((mask >> (c[i] - 1)) & 1) {
			nc[i] = 0;
		}
		else {
			nc[i] = c[i];
		}
	}
	for (int i = 0; i < n; i++) {
		if (nc[i] == 0) {
			dfs(i);
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!used[i] && !nc[i]) {
			return false;
		}
	}
	return true;
}

int get(int mask) {
	return __builtin_popcount(mask);
}

int ans;

void run() {
	ans = k - 1;
	for (int mask = 1; mask < (1 << k); mask++) {
		if (check(mask)) {
			//cout << mask << endl;
			chkmin(ans, get(mask) - 1);
		}
	}
}

void write() {
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