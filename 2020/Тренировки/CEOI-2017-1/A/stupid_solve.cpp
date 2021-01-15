#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m;
vector<pair<int,int>> ed;
int q;
vector<pair<int, int>> need;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ed.push_back({u, v});
	}
	cin >> q;
	need.resize(q);
	for (auto &i : need) {
		cin >> i.first >> i.second;
		i.first--;
		i.second--;
	}
}

bool find(int v, int need, vector<bool> & used, vector<vector<int>> & g) {
	if (need == v) return true;
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			if (find(i, need, used, g)) {
				return true;
			}
		}
	}
	return false;
}

bool check(int mask) {
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		if ((mask >> i) & 1) {
			g[ed[i].second].push_back(ed[i].first);
		}
		else {
			g[ed[i].first].push_back(ed[i].second);
		}
	}
	for (auto i : need) {
		vector<bool> used(n, 0);
		//cout << i.first << " " << i.second << endl;
		if (!find(i.first, i.second, used, g)) {
			return false;
		}
	}
	return true;
}

vector<bool> used[2];

void run() {
	used[0].assign(m, 0);
	used[1].assign(m, 0);
	for (int mask = 0; mask < (1 << m); mask++) {
		if (!check(mask)) continue;
		//cout << mask << endl;
		for (int i = 0; i < m; i++) {
			used[(mask >> i) & 1][i] = true;
		}
 	}
}

void write() {
	for (int i = 0; i < m; i++) {
		if (!used[0][i] && !used[1][i]) {
			cout << -1 << endl;
			exit(0);
		}
	}
	for (int i = 0; i < m; i++) {
		if (used[0][i] && used[1][i]) {
			cout << "B";
		}
		else if (used[0][i]) {
			cout << "R";
		}
		else {
			cout <<  "L";
		}
	}
	cout << endl;
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