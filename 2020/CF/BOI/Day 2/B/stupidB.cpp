#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

const int N = 10, LOG = 4;
int n;
vector<int> g[N];

int tin[N], tout[N], timer = 0, h[N], dp[N][LOG];
vector<int> order;

void dfs(int v, int p) {
	order.push_back(v);
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < LOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (auto i : g[v]) {
		if (i == p) continue;
		h[i] = h[v] + 1;
		dfs(i, v);
	}
	tout[v] = timer++;
}

bool isUpper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (isUpper(v, u)) return v;
	if (isUpper(u, v)) return u;
	for (int i = LOG - 1; i >= 0; i--) {
		if (!isUpper(dp[v][i], u)) {
			v = dp[v][i];
		}
	}
	return dp[v][0];
}

int dist(int u, int v) {
	return h[v] + h[u] - 2 * h[lca(v, u)];
}

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

ll ans = 1e18;
vector<int> fans;

void relax(vector<int> order) {
	ll myAns = 0;
	for (int i = 0; i < n; i++) {
		if (order[i] == i) return;
		myAns += dist(i, order[i]);
	}
	if (ans <= myAns) return;
	ans = myAns;
	fans = order;
}

void run() {
	dfs(0, 0);
	vector<int> order(n);
	iota(all(order), 0);
	do {
		relax(order);
	} while (next_permutation(all(order)));
}

void write() {
	cout << ans << endl;
	return;
	for (auto i : fans) {
		cout << i + 1 << " ";
	}
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}