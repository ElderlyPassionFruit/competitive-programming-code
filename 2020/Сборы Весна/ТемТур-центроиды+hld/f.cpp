#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;
int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
}

vector<int> have[MAXN];
int tin[MAXN], tout[MAXN], timer = 0;
int h[MAXN];

void dfs(int v, int len) {
	h[v] = len;
	tin[v] = timer++;
	have[len].push_back(tin[v]);
	for (auto i : g[v]) {
		dfs(i, len + 1);
	}
	tout[v] = timer;
}

void run() {
	dfs(0, 0);
	int q;
	cin >> q;
	while (q--) {
		int v, add;
		cin >> v >> add;
		v--;
		if (h[v] + add >= n) {
			cout << "0\n";
		} else {
			cout << (lower_bound(all(have[h[v] + add]), tout[v]) - lower_bound(all(have[h[v] + add]), tin[v])) << "\n";
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