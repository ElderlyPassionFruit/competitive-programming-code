#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 2e5 + 10;
vector<int> g[MAXN];
int c[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[p].push_back(i);
	}
	for (int i = 1; i < n; i++) {
		cin >> c[i];
	}
}

ll ans;
ll sum[MAXN];
int sz[MAXN];
int mn[MAXN];

void dfs_calc(int v) {
	sum[v] = c[v];
	sz[v] = 1;
	mn[v] = c[v];
	for (auto i : g[v]) {
		dfs_calc(i);
		sum[v] += sum[i];
		chkmin(mn[v], mn[i]);
		sz[v] += sz[i]; 
	}
}

struct event{
	ll sum;
	int sz;
	int mn;
	event() {}
	event(ll _sum, int _sz, int _mn) {
		sum = _sum, sz = _sz, mn = _mn;
	}
};

bool operator<(const event & a, const event & b) {
	return a.sz < b.sz;
}

void dfs_solve(int v) {
	if (g[v].empty()) return;

	ll add = 0;

	vector<event> have;
	for (auto i : g[v]) {
		have.push_back({sum[i], sz[i], mn[i]});
		ans += sum[i];
		add += sum[i];
	}

	assert(have.size() >= 2);
	sort(all(have));

	int sz = 0;
	for (int i = 0; i < have.size() - 1; i++) {
		sz += have[i].sz;
	}

	if (sz < have.back().sz) {
		int mn = 1e9 + 228;
		for (int i = 0; i < have.size() - 1; i++) {
			chkmin(mn, have[i].mn);
		}
		ans += (ll)mn * (have.back().sz - sz);
		add += (ll)mn * (have.back().sz - sz);
	}
	else if ((sz + have.back().sz) % 2) {
		sort(all(have), [&] (event i, event j) {return i.mn < j.mn;});
		ans += have[0].mn;
	}

	//cout << "v = " << v << " add = " << add << endl; 

	for (auto i : g[v]) {
		dfs_solve(i);
	}
} 

void run() {
	dfs_calc(0);
	dfs_solve(0);
}

void write() {
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