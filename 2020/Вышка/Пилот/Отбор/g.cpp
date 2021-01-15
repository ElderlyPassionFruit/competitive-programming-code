#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int N = 1e5 + 10;
int n;
vector<pair<int, int>> g[N];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
}

int h[N];

void dfs(int v, int p) {
	for (auto i : g[v]) {
		if (i.first == p) continue;
		h[i.first] = h[v] ^ i.second;
		dfs(i.first, v);
	}
}

const int LOG = 33;
const int MEM = N * LOG;
int nxt[MEM][2];
int fans[MEM];
int root = 1;
int topQ = 2;

void add(int val, int u) {
	int now = root;
	for (int i = LOG - 1; i >= 0; i--) {
		int bit = (val >> i) & 1;
		if (!nxt[now][bit]) {
			nxt[now][bit] = topQ++;
		}
		now = nxt[now][bit];
	}
	fans[now] = u;
}

int get(int val) {
	int now = root;
	int ans = 0;
	for (int i = LOG - 1; i >= 0; i--) {
		int bit = ((val >> i) & 1) ^ 1;
		if (!nxt[now][bit]) bit ^= 1;
		assert(nxt[now][bit]);
		ans ^= ((val >> i) & 1) ^ bit;
		now = nxt[now][bit];
	}
	return fans[now];
}

pair<int, pair<int, int>> ans;

void run() {
	dfs(0, 0);
	for (int i = 0; i < n; i++) {
		add(h[i], i);
	}
	ans = {-1, {-1, -1}};
	for (int i = 0; i < n; i++) {
		int u = get(h[i]);
		chkmax(ans, make_pair(h[i] ^ h[u], make_pair(i, u)));
	}
}

void write() {
	cout << ans.second.first + 1 << " " << ans.second.second + 1 << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}