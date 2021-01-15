#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 300;
int n, m;
vector <int> g[MAXN];
vector <bool> used;
int mt[MAXN];

bool dfs (int v) {
	if (used[v]) return false;
	used[v] = true;
	for (auto to : g[v]) {
		if (mt[to] == -1 || dfs(mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int v;
		while (cin >> v) {
			if (v == 0)
				break;
			v--;
			g[i].push_back(v);
		}
	}
	for (int i = 0; i < m; i++) {
		mt[i] = -1;
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		used.assign(n, false);
		dfs(i);
	}
}

void write() {
	vector <pair <int, int> > ans;
	for (int i = 0; i < m; i++) {
		if (mt[i] != -1) {
			ans.push_back({mt[i] + 1, i + 1});
		}
	}
	cout << ans.size() << endl;
	for (auto i : ans) {
		cout << i.first << " " << i.second << endl;
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