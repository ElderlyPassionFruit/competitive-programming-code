#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
map<int, int> in[MAXN], out[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		in[v][u] += -cost;
		out[u][v] += -cost;
	}
}

bool used[MAXN];
queue<int> q;

void add(int u, int v, int cost) {
	if (u == v) return;
	if (cost == 0) return;
	in[v][u] -= cost;
	out[u][v] -= cost;
}

void run() {
	for (int i = 0; i < n; i++) {
		q.push(i);
		used[i] = true;
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		used[v] = false;
		while (!in[v].empty() && !out[v].empty()) {
			auto a = *in[v].begin();
			in[v][a.second] += a.second;
			out[a.second].erase(v);
			out[a.second][a.first] += a.second;
			if (a.second == v) continue;
			auto b = *out[v].begin();
			out[v].erase(out[v].begin());
			in[b.to].erase({v, b.cost});
			if (b.to == v) continue;

			int x = min(a.cost, b.cost);
			a.cost -= x;
			b.cost -= x;
			if (!used[b.to]) {
				used[b.to] = true;
				q.push(b.to);
			}
			add(a.to, v, a.cost);
			add(v, b.to, b.cost);
			add(a.to, b.to, x);
		}
	}
}

void write() {
	vector<vector<ll> > ans;
	for (int i = 0; i < n; i++) {
		for (auto j : out[i]) {
			if (j.to != i)
				ans.push_back({i + 1, j.to + 1, j.cost});
		}
	}
	sort(all(ans));
	vector<vector<ll> > fans;
	for (auto i : ans) {
		if (fans.empty() || fans.back()[0] != i[0] || fans.back()[1] != i[1])
			fans.push_back(i);
		else
			fans[fans.size() - 1][2] += i[2];
	}
	ans = fans;
	cout << ans.size() << "\n";
	for (auto i : ans) {
		for (auto j : i)
			cout << j << " ";
		cout << "\n";
	}
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