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

#define int long long

const int INF = 1e18 + 239;
const int N = 200;

namespace F {
	int a[N];
	int f[N];

	void add(int pos, int val) {
		for (int i = pos; i < N; i = (i | (i + 1))) {
			f[i] += val;
		}
	}

	void set(int pos, int val) {
		add(pos, val - a[pos]);
		a[pos] = val;
	}

	int sum(int r) {
		int ans = 0;
		for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
			ans += f[i];
		}
		return ans;
	}

	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	void init() {
		fill(f, f + N, 0);
		fill(a, a + N, 0);
	}
}

int n;
int a[N];
int b[N];
int p[N];

int sbig[N];
int wr[N];
int sprev[N];

vector<int> pos[N];
vector<int> qpos[N];

void init() {
	for (int i = 0; i < n; i++) {
		pos[a[i]].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		if (wr[a[i]] > 0) {
			qpos[b[wr[a[i]] - 1]].push_back(i);
		}
	}
	//
	F::init();
	for (int i = 0; i < n; i++) {
		if (p[i] < 0) F::set(i, p[i]);
	}
	for (int i = N - 1; i >= 0; i--) {
		for (auto v : pos[i]) {			
			sbig[v] = F::sum(v + 1, N - 1);
		}
		for (auto v : qpos[i]) {
			sprev[v] = F::sum(v + 1, N - 1);
		}
		for (auto v : pos[i]) {
			F::set(v, p[v]);
		}
	}
}

int mn[N];
int dp[N];

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	fill(wr, wr + N, -1);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i];
	}
	{
		vector<int> sn;
		for (int i = 0; i < n; i++) sn.push_back(a[i]);
		for (int i = 0; i < m; i++) sn.push_back(b[i]);
		sort(sn.begin(), sn.end());
		sn.resize(unique(sn.begin(), sn.end()) - sn.begin());
		for (int i = 0; i < n; i++) a[i] = lower_bound(sn.begin(), sn.end(), a[i]) - sn.begin();
		for (int i = 0; i < m; i++) b[i] = lower_bound(sn.begin(), sn.end(), b[i]) - sn.begin();
	}
	for (int i = 0; i < m; i++) {
		wr[b[i]] = i;
	}
	init();
	fill(dp, dp + N, INF);
	fill(mn, mn + N, INF);
	{
		int cs = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] == b[0]) {
				dp[i] = cs;
			}
			cs += p[i];
		}
	}
	int ans = INF;
	for (int i = 0; i < n; i++) {
		if (wr[a[i]] != -1) {
			int w = wr[a[i]];
			int c = INF;
			if (w > 0) c = mn[w - 1];
			if (c != INF) dp[i] = min(dp[i], c - sprev[i] - p[i]);
			mn[w] = min(mn[w], dp[i] + sbig[i]);
		}
	}
	int cs = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] == b[m - 1]) {
			if (dp[i] != INF) {
				ans = min(ans, dp[i] + cs);
			}
		}
		if (a[i] > b[m - 1]) cs += p[i];
		else if (p[i] < 0) cs += p[i];
	}
	if (ans == INF) {
		cout << "NO\n";
	} else {
		cout << "YES\n";
		cout << ans << '\n';
	}
}
