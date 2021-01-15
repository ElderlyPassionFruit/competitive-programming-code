#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 5010;
set <pair <int, int> > need, bad, have;
set <int> g[MAXN];
int n;
void read() {
	cin >> n;
	for (int i = 0 ; i < n - 1; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		if (v > u) swap(v, u);
		g[u].insert(v);
		g[v].insert(u);
		have.insert({v, u});
	}
	for (int i = 0; i < n - 1; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		if (v > u) swap(v, u);
		need.insert({v, u});
	}
	for (auto i : have) {
		if (need.find(i) == need.end()) {
			bad.insert(i);
		}
		else {
			need.erase(i);
		}
	}
}
vector <vector <int> > ans;
vector <int> used;

void dfs(int v, int p, int color) {
	used[v] = color;
	for (auto i : g[v]) {
		if (i != p) {
			dfs(i, v, color);
		}
	}
}

void run() {
	for (auto i : bad) {
		int v = i.first, u = i.second;
		g[v].erase(u);
		g[u].erase(v);
		used.assign(n, false);
		dfs(v, v, 1);
		dfs(u, u, 2);
		pair <int, int> good = {-1, -1};
		for (auto j : need) {
			if (used[j.first] != used[j.second]) {
				good = j;
				break;
			}
		}
		g[good.first].insert(good.second);
		g[good.second].insert(good.first);
		ans.push_back({v, u, good.first, good.second});
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans) {
		for (auto j : i) {
			cout << j + 1 << " ";
		}
		cout << endl;
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