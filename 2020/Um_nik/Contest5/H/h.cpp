#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	ll x, y;
	pt() {}
	pt(ll _x, ll _y) {
		x = _x, y = _y;
	}
};

pt operator-(const pt & a, const pt & b) {
	return pt(a.x - b.x, a.y - b.y);
}

ll operator^(const pt & a, const pt & b) {
	return a.x * b.y - a.y * b.x;
}

int sign(ll x) {
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n;
pt a[MAXN];

vector<int> g[MAXN];
int dp[MAXN][MAXLOG], tin[MAXN], tout[MAXN], timer = 0;

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++) {
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	}
	for (auto i : g[v]) {
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
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if (!isUpper(dp[v][i], u)) {
			v = dp[v][i];
		}
	}
	return dp[v][0];
}

int p[MAXN];

bool checkJump(int l, int x, int r) {
	return sign((a[x] - a[l]) ^ (a[r] - a[l])) > 0;
}

void findJump(int l) {
	p[l] = l + 1;
	while (p[l] != n - 1 && checkJump(l, p[l], p[p[l]])) {
		p[l] = p[p[l]];
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	p[n - 1] = -1;
	for (int i = n - 2; i >= 0; i--) {
		findJump(i);	
	}
	for (int i = 0; i < n - 1; i++) {
		g[p[i]].push_back(i);
	}
	dfs(n - 1, n - 1);
	int q;
	cin >> q;
	while (q--) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		cout << lca(u, v) + 1 << " ";
	}
	cout << endl;
	return 0;
}