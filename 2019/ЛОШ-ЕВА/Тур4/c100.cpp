#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10, MAXC = 21, MOD = 10007;
short tree[1 << 18][MAXC], a[MAXN], b[MAXN];
int n, c, q;

long long help[MAXC];

inline void merge(int v) {
	for (int i = 0; i <= c; i++)
		help[i] = 0;
	for (int i = 0; i <= c; i++) {
		for (int j = 0; j <= c; j++) {
			help[min(i + j, c)] += (long long) tree[v * 2][i] * tree[v * 2 + 1][j];
		}
	}
	for (int i = 0; i <= c; i++)
		tree[v][i] = help[i] % MOD;
}

inline void build() {
	int max_num = 1;
	while (max_num < 2 * n) {
		max_num *= 2;
	}
	for (int i = 0; i < max_num; i++)
		tree[i][0] = 1;

	for (int i = n; i < max_num; i++)
		tree[i][0] = b[i - n], tree[i][1] = a[i - n];
	
	for (int i = n - 1; i >= 1; i--)
		merge(i);
}

inline void upd(int p) {
	int v = p + n;
	tree[v][0] = b[p];
	tree[v][1] = a[p];
	v /= 2;
	while (v) {
		merge(v);
		v /= 2;
	}
}

inline void read() {
	cin >> n >> c;
	for (int i = 0; i < n; i++){
		int x;
		cin >> x;
		x %= MOD;
		a[i] = x;
	}
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x %= MOD;
		b[i] = x;
	}
	build();
}

inline void run() {
	cin >> q;
	for (int test = 0; test < q; test++) {
		int pos, x, y;
		cin >> pos >> x >> y;
		x %= MOD;
		y %= MOD;
		pos--;
		a[pos] = x;
		b[pos] = y;
		upd(pos);
		cout << tree[1][c] << "\n";	
	}
}

inline void write() {

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