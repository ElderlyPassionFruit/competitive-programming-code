#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 2 * 1e5 + 10;

int tree[MAXN * 4];
int mod[MAXN * 4];

inline void push(int v) {
	mod[v * 2] += mod[v];
	mod[v * 2 + 1] += mod[v];
	mod[v] = 0;
}

inline int get_val(int v) {
	return mod[v] + tree[v];
}

void upd(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) {
		return;
	}

	if (tl >= l && tr <= r) {
		mod[v] += val;
		return;
	}
	push(v);
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = min(get_val(v * 2), get_val(v * 2 + 1));
}

int get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l)
		return 1e18;
	if (tl >= l && tr <= r)
		return get_val(v);
	push(v);
	int tm = (tl + tr) / 2;
	int ans = min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	tree[v] = min(get_val(v * 2), get_val(v * 2 + 1));
	return ans;
}

int n, m, k;

void read() {
	cin >> n >> k >> m;
	n++;
	upd(1, 0, n, 0, n, k);
}

vector <int> ans;
void run() {
	for (int test = 0; test < m; test++) {
		int l, r;
		cin >> l >> r;
		int ax = get(1, 0, n, l, r);
		if (ax == 0) {
			ans.push_back(0);
		}
		else {
			ans.push_back(1);
			upd(1, 0, n, l, r, -1);
		}
	}
}

void write() {
	for (auto i : ans) {
		cout << i << '\n';
	}
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