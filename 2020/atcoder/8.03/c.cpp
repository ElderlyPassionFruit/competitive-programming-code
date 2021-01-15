#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
int n;
vector<int> g[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

vector<int> comp[2];

void dfs(int v, int p, int c) {
	comp[c].push_back(v);
	for (auto i : g[v]) {
		if (i == p) continue;
		dfs(i, v, c ^ 1);
	}
}

vector<int> cnt[3];
vector<int> ans;

void run() {
	dfs(0, -1, 0);
	if (comp[0].size() > comp[1].size()) swap(comp[0], comp[1]);
	
	for (int i = 1; i <= n; i++) {
		cnt[i % 3].push_back(i);
	}
	
	ans.resize(n);
	
	if (comp[0].size() <= cnt[0].size()) {
		for (auto i : comp[0]) {
			ans[i] = cnt[0].back();
			cnt[0].pop_back();
		}
		for (auto i : comp[1]) {
			if (!cnt[0].empty()) {
				ans[i] = cnt[0].back();
				cnt[0].pop_back();
			}
			else if (!cnt[1].empty()) {
				ans[i] = cnt[1].back();
				cnt[1].pop_back();
			}
			else if (!cnt[2].empty()) {
				ans[i] = cnt[2].back();
				cnt[2].pop_back();
			}
		}
		return;
	}


	for (auto i : comp[0]) {
		if (!cnt[1].empty()) {
			ans[i] = cnt[1].back();
			cnt[1].pop_back();
		}
		else {
			assert(!cnt[0].empty());
			ans[i] = cnt[0].back();
			cnt[0].pop_back();
		}
	}

	assert(cnt[1].empty());
	
	for (auto i : comp[1]) {
		if (!cnt[2].empty()) {
			ans[i] = cnt[2].back();
			cnt[2].pop_back();
		}
		else {
			assert(!cnt[0].empty());
			ans[i] = cnt[0].back();
			cnt[0].pop_back();
		}
	}
}

void write() {
	for (auto i : ans) {
		cout << i << " ";
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