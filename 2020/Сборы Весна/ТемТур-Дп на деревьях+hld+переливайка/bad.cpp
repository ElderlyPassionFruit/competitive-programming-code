#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
int n, d;

void read() {
	cin >> n >> d;
	if (d % 2 == 1) {
		cout << 0 << endl;
		exit(0);
	}
	d /= 2;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int ans = 0;
vector<int> cnt;

void dfs(int v, int p, int len) {
	if (len == 0) {
		cnt[cnt.size() - 1]++;
		return;
	}
	len--;
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v, len);
	}
}

void run() {
	ans = 0;
	for (int i = 0; i < n; i++) {
		cnt.clear();
		for (auto j : g[i]) {
			cnt.push_back(0);
			dfs(j, i, d - 1);
		}
		int sum = 0;
		int mul = 0;
		for (int x = 0; x < (int)cnt.size(); x++) {
			ans += mul * cnt[x];
			mul += sum * cnt[x];
			sum += cnt[x];
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