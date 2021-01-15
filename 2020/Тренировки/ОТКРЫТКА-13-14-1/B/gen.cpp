#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());
 
int get(int l, int r) {
	return rng() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	n = get(8, 10);
	m = get(5, 10);
	cout << n << " " << m << endl;
	for (int i = 0; i < n; i++) {
		cout << get(1, 10) << " ";
	} 
	cout << endl;
	set<pair<int, int>> edge;
	for (int i = 0; i < m; i++) {
		int u = get(1, n);
		int v = get(1, n);
		while (u == v || edge.count({min(u, v), max(u, v)})) {
			u = get(1, n);
			v = get(1, n);
		}
		edge.insert({min(u, v), max(v, u)});
		cout << u << " " << v << endl;
	}
	return 0;
}