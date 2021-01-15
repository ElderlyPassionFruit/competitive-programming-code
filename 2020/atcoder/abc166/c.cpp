#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, m;
int h[MAXN];
vector<int> g[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> h[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans;

void run() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		bool flag = true;
		for (auto j : g[i]) {
			if (h[i] > h[j]) continue;
			flag = false;
		}
		ans += flag;
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