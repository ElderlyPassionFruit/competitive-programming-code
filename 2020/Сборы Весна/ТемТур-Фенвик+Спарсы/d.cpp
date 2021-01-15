#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int INF = 1e9 + 10;
const int MOD = 1e9 + 7;
int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

struct Item{
	int x1, y1, x2, y2;
	Item() {
		x1 = -INF, y1 = -INF, x2 = INF, y2 = INF;
	}
	Item(int _x1, int _y1, int _x2, int _y2) {
		x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
	}
	void make() {
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
	}
	ll get() {
		return mul(max(0LL, x2 - x1), max(0LL, y2 - y1));
	}
};

Item merge(const Item & a, const Item & b) {
	return Item(max(a.x1, b.x1), max(a.y1, b.y1), min(a.x2, b.x2), min(a.y2, b.y2));
}

struct sparse_table2D{
	vector<vector<vector<vector<Item>>>> sparse;
	vector<int> lg;
	int n, m;

	sparse_table2D() {}

	sparse_table2D(const vector<vector<Item>> & a) {
		n = a.size();
		m = a[0].size();
		lg.resize(max(n, m) + 1, 0);
		for (int i = 2; i <= max(n, m); i++) {
			lg[i] = lg[i / 2] + 1;
		}
		sparse.assign(n, vector<vector<vector<Item>>> (m, vector<vector<Item>> (lg[n] + 1, vector<Item> (lg[m] + 1, Item()))));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				sparse[i][j][0][0] = a[i][j];
			}
		}
		for (int l = 1; l <= lg[m]; l++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j + (1 << l) <= m; j++) {
					sparse[i][j][0][l] = merge(sparse[i][j][0][l - 1], sparse[i][j + (1 << (l - 1))][0][l - 1]);
				}
			}
		}
		for (int l1 = 0; l1 <= lg[m]; l1++) {
			for (int l2 = 1; l2 <= lg[n]; l2++) {
				for (int j = 0; j + (1 << l1) <= m; j++) {
					for (int i = 0; i + (1 << l2) <= n; i++) {
						sparse[i][j][l2][l1] = merge(sparse[i][j][l2 - 1][l1], sparse[i + (1 << (l2 - 1))][j][l2 - 1][l1]);
					}
				}
			}
		}
	}

	Item get(int l1, int r1, int l2, int r2) {
		if (l1 > r1) swap(l1, r1);
		if (l2 > r2) swap(l2, r2);
		int lg1 = lg[r1 - l1];
		int lg2 = lg[r2 - l2];
		Item ans;
		ans = merge(ans, sparse[l1][l2][lg1][lg2]);
		ans = merge(ans, sparse[r1 - (1 << lg1) + 1][l2][lg1][lg2]);
		ans = merge(ans, sparse[l1][r2 - (1 << lg2) + 1][lg1][lg2]);
		ans = merge(ans, sparse[r1 - (1 << lg1) + 1][r2 - (1 << lg2) + 1][lg1][lg2]);
		return ans;
	}
};

int n, m;
vector<vector<Item>> a;

void read() {
	cin >> n >> m;
	a.resize(n, vector<Item> (m, Item()));
	for (auto &i : a) {
		for (auto &j : i) {
			cin >> j.x1 >> j.y1 >> j.x2 >> j.y2;
			j.make();
		}
	}
}

int ans;

void run() {
	sparse_table2D sparse(a);
	ans = 0;
	int q;
	cin >> q;
	int A, B, v0;
	cin >> A >> B >> v0;
	while (q--) {
		int v1 = add(mul(A, v0), B);
		int v2 = add(mul(A, v1), B);
		int v3 = add(mul(A, v2), B);
		int v4 = add(mul(A, v3), B);
		ans = add(ans, sparse.get(v1 % n, v3 % n, v2 % m, v4 % m).get());
		v0 = v4;
	}
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