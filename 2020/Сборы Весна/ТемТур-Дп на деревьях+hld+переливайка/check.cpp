#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void no() {
	cout << "PE";
	exit(0);
}

int n;
vector<vector<int>> g;
int len;

void read() {
	cin >> n;
	g.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cin >> len;
	int u, v;
	int cnt = 0;
	while (cin >> u >> v) {
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		cnt++;
	}
	//cerr << "len = " << len << endl;
	//cerr << "cnt = " << cnt << endl;
	if (cnt < 1 || cnt > 2) {
		no();
	}
	for (int i = 0; i < n; i++) {
		sort(all(g[i]));
		int sz = g[i].size();
		g[i].resize(unique(all(g[i])) - g[i].begin());
		if (g[i].size() != sz) {
			no();
		}
	}
}

void check(vector<int> have) {
	while (have.size() > len) have.pop_back();
	have.push_back(have[0]);
	for (int i = 1; i < (int)have.size(); i++) {
		bool flag = false;
		for (auto v : g[have[i]]) {
			if (v == have[i - 1]) {
				flag = true;
				break;
			}
		}
		if (!flag) return;
	}
	cout << "OK";
	exit(0);
}

void run() {
	vector<int> have(n);
	iota(all(have), 0);
	do {
		check(have);
	} while (next_permutation(all(have)));
}

void write() {
	no();
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