#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 51;

vector<int> g[MAXN];
vector<int> gr[MAXN];
int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (s[j] == 'N') continue;
			g[i].push_back(j);
			gr[j].push_back(i);
		}
	}
}

vector<int> order;
vector<bool> used;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_order(i);
		}
	}
	order.push_back(v);
}

vector<int> color;
vector<vector<int> > comp;

void dfs_color(int v, int c) {
	color[v] = c;
	comp[c].push_back(a[v]);
	for (auto i : gr[v]) {
		if (color[i] == -1) {
			dfs_color(i, c);
		}
	}
} 

int c;

void build() {
	used.assign(n, 0);
	for (int i = 0; i < n; i++)
		if (!used[i])
			dfs_order(i);

	used.assign(n, 0);
	reverse(all(order));
	color.assign(n, -1);
	comp.resize(n);
	c = 0;
	for (auto i : order)
		if (color[i] == -1)
			dfs_color(i, c++);
	for (int i = 0; i < n; i++)
		g[i].clear();
	for (int i = 0; i < n; i++) {
		for (auto j : gr[i]) {
			int u = color[i];
			int v = color[j];
			if (u == v) continue;
			g[u].push_back(v);
		}
	}
}

ld ans;

void solve() {
	ans = 1e9;
	vector<int> have;
	int sum = 0, cnt = 0;
	for (int i = 0; i < c; i++) {
		if (!g[i].empty()) {
			for (int j = 0; j < comp[i].size(); j++) 
				have.push_back(comp[i][j]);
			continue;
		}
		sort(all(comp[i]));
		sum += comp[i][0];
		cnt++;
		for (int j = 1; j < comp[i].size(); j++)
			have.push_back(comp[i][j]);
	}
	sort(all(have));
	chkmin(ans, (ld) sum / cnt);
	for (auto i : have) {
		sum += i;
		cnt++;
		chkmin(ans, (ld) sum / cnt);
	}
}

void run() {
	build();
	solve();
}

void write() {
	cout.precision(20);
	cout.setf(ios::fixed);
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