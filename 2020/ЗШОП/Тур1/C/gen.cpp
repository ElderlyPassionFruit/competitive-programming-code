#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(int l, int r) {
	return rand() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(time(0));
	int n = get(2, 6);
	int m = get(n - 1, 10);
	int k = get(1, m);
	//cout << n << " " << m << " " << k << endl;
	set<pair<int, int> > edges;
	for (int i = 2; i <= n; i++) {
		int u = get(1, i - 1);
		int v = i;
		edges.insert({u, v});	
	}
	m -= n - 1;
	for (int i = 0; i < m; i++) {
		int u = get(1, n);
		int v = get(1, n);
		if (u == v) continue;
		if (u > v) swap(u, v);
		edges.insert({u, v});
	}
	m = edges.size();
	k = get(1, m);
	cout << n << " " << m << " " << k << endl;
	for (auto i : edges) {
		cout << i.first << " " << i.second << endl;
	}
	set<int> used;
	for (int i = 0; i < k; i++) {
		int x = get(1, m);
		while (used.count(x)) {
			x = get(1, m);
		}
		used.insert(x);
		cout << x << endl;
	}
	return 0;
}