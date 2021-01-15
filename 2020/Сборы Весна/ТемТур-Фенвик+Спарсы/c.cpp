#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct sparse_table{
	const int INF = 1e9 + 10;
	vector<vector<int>> sparse;
	int n;
	vector<int> lg;

	int merge(int a, int b) {
		return min(a, b);
	}

	sparse_table() {}

	sparse_table(const vector<int> & a) {
		n = a.size();
		lg.assign(n + 1, 0);
		for (int i = 2; i <= n; i++) {
			lg[i] = lg[i / 2] + 1;
		}
		sparse.assign(n, vector<int> (lg.back() + 1, INF));
		for (int i = 0; i < n; i++)
			sparse[i][0] = a[i];
		for (int l = 1; l <= lg.back(); l++) {
			for (int i = 0; i + (1 << l) <= n; i++) {
				sparse[i][l] = merge(sparse[i][l - 1], sparse[i + (1 << (l - 1))][l - 1]);
			}
		}
	}

	int get(int l, int r) {
		l--;
		r--;
		if (r < l) swap(l, r);
		int log = lg[r - l];
		int my_ans = merge(sparse[l][log], sparse[r - (1 << log) + 1][log]);
		return my_ans;
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, a0;
	cin >> n >> m >> a0;
	vector<int> a;
	a.push_back(a0);
	for (int i = 0; i < n - 1; i++) {
		a.push_back((a.back() * 23 + 21563) % 16714589);
	}
	cout << endl;
	sparse_table sparse(a);
	int u, v;
	cin >> u >> v;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		ans = sparse.get(u, v);
		if (i == m) break;
		u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
		v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
	}
	cout << u << " " << v << " " << ans << "\n";
	return 0;
}