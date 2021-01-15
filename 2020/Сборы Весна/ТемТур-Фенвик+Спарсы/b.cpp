#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct fenvik3D{
	vector<vector<vector<int>>> tree;
	int n;
	fenvik3D(int _n) {
		n = _n;
		tree.assign(n, vector<vector<int>> (n, vector<int> (n, 0)));
	}

	void upd(int x, int y, int z, int val) {
		for (int i = x; i < n; i |= i + 1)
			for (int j = y; j < n; j |= j + 1)
				for (int k = z; k < n; k |= k + 1)
					tree[i][j][k] += val;
	}

	int get(int x, int y, int z) {
		int ans = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
					ans += tree[i][j][k];
				}
			}
		}
		return ans;
	}

	int get(int x1, int y1, int z1, int x2, int y2, int z2) {
		int ans = 0;
		ans += get(x2, y2, z2);
		ans -= get(x1 - 1, y2, z2);
		ans -= get(x2, y1 - 1, z2);
		ans -= get(x2, y2, z1 - 1);
		ans += get(x2, y1 - 1, z1 - 1);
		ans += get(x1 - 1, y2, z1 - 1);
		ans += get(x1 - 1, y1 - 1, z2);
		ans -= get(x1 - 1, y1 - 1, z1 - 1);
		return ans;
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	fenvik3D tree(n);
	int t;
	while (cin >> t) {
		if (t == 3) break;
		if (t == 1) {
			int x, y, z, val;
			cin >> x >> y >> z >> val;
			tree.upd(x, y, z, val);
		} else {
			int x1, y1, z1, x2, y2, z2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
			cout << tree.get(x1, y1, z1, x2, y2, z2) << "\n";
		}
	}
	return 0;
}