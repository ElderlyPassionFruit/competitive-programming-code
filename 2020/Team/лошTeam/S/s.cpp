#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime> 
#include <bitset>
#include <complex>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	vector<int> in(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		in[v]++;
	} 
	vector<int> al(n, 1);
	set<int> s;
	auto ers = [&](int x) {
		if (al[x]) {
			s.erase(x);
			in[x]--;
			if (!in[x]) s.insert(x);
		}
	};
	for (int i = 0; i < n; i++) {
		if (!in[i]) {
			s.insert(i);
		}
	}
	vector<int> ans(n);
	int p = 0;
	while (!s.empty()) {
		int v = *s.begin();
		// ans.push_back(v);
		al[v] = 0;
		ans[v] = p;
		s.erase(s.begin());
		for (auto t : g[v]) {
			ers(t);
		}
		p++;
	}
	for (auto t : ans) {
		cout << t + 1 << ' ';
	}
	cout << '\n';
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solve();
}