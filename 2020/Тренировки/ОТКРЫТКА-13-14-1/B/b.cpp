#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;

int n, m;
vector<int> g[MAXN];
vector<pair<int, int>> ed;
int p[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		ed.push_back({u, v});
	}
}

int ans = 0;
vector<int> fans;

void relax(vector<int> v) {
	set<int> have;
	for (auto i : v) {
		have.insert(i);
	}
	if (v.size() != have.size()) return;
	int Fans = 0;
	for (auto i : v) {
		Fans += p[i];
	}
	if (Fans > ans) {
		ans = Fans;
		fans = v;
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		relax({i});
		for (auto j : g[i]) {
			relax({i, j});
		}
		if (g[i].size() < 2) continue;
		sort(all(g[i]), [&] (int a, int b) {return p[a] > p[b];});
		relax({g[i][0], i, g[i][1]});
		while (g[i].size() > 3) {
			g[i].pop_back();
		}
	}
	for (auto [u, v] : ed) {
		for (auto i : g[u]) {
			for (auto j : g[v]) {
				relax({i, u, v, j});
			}
		}
	}
}

void write() {
	cout << fans.size() << "\n";
	for (auto i : fans) {
		cout << i + 1 << " ";
	}
	cout << "\n";
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