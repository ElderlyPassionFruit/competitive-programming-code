#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());  
const int MAXN = 2e5;
vector<int> in[MAXN], out[MAXN];
vector<int> nowIn[MAXN], nowOut[MAXN];
int n, m;

void build() {

}

void solve(vector<int> & order) {

}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		in[i].clear();
		out[i].clear();
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		in[b].push_back(a);
		out[a].push_back(b);
	}
	vector<int> order(n);
	iota(all(order), 0);
	while (true) {
		shuffle(all(order), rng);
		build();
		if (solve(order)) return; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}