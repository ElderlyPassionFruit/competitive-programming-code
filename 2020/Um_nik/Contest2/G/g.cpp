#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10, MAXLOG = 20;
int n, m;
vector<int> g[MAXN];

bool used[MAXN];
int sz[MAXN];
int dist[MAXN][MAXLOG];
int centr;
int centrH[MAXN];
int par[MAXN];

void dfsCentr(int v, int p, int size, int len, int h) {
	if (h != -1) {
		dist[v][h] = len++;
	}
	int mx = 0;
	sz[v] = 1;
	for (auto i : g[v]) {
		if (used[i]) continue;
		if (i == p) continue;
		dfsCentr(i, v, size, len, h);
		sz[v] += sz[i];
		mx = max(mx, sz[i]);
	}
	mx = max(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

void buildCentr(int v, int size, int h) {
	used[v] = true;
	centrH[v] = ++h;
	for (auto i : g[v]) {
		if (used[i]) continue;
		int fsz = sz[i];
		if (fsz > sz[v]) {
			fsz = size - sz[v];
		}
		dfsCentr(i, v, fsz, 1, h);
		par[centr] = v;
		buildCentr(centr, fsz, h);
	}
}

int ans[MAXN];
void build() {
	fill(ans, ans + n, n);
	fill(par, par + n, -1);
	dfsCentr(0, -1, n, 0, -1);
	buildCentr(centr, n, -1);
}



void paint(int v) {
	int now = v;
	for (int h = centrH[v]; h >= 0; h--) {
		ans[now] = min(ans[now], dist[v][h]);
		now = par[now];
	}
}

int get(int v) {
	int fans = n;
	int now = v;
	for (int h = centrH[v]; h >= 0; h--) {
		fans = min(fans, ans[now] + dist[v][h]);
		now = par[now];
	}
	return fans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int q;
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	build();
	//cout << "buildOk" << endl;
	paint(0);
	while (q--) {
		int t, v;
		cin >> t >> v;
		v--;
		if (t == 1) {
			paint(v);
		} else {
			cout << get(v) << "\n";
		}
	}
	return 0;
}