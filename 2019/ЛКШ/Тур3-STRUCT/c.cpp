#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, q;
vector<int> tree[MAXN * 4];
int arr[MAXN];

void build(int v, int tl, int tr) {
	if (tl == tr - 1) {
		tree[v] = {arr[tl]};
		return;
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm, tr);
	tree[v].resize(tree[v * 2].size() + tree[v * 2 + 1].size());
	merge(tree[v * 2].begin(), tree[v * 2].end(), tree[v * 2 + 1].begin(), tree[v * 2 + 1].end(), tree[v].begin());
}

int get(int v, int tl, int tr, int l, int r, int x, int y) {
	if (tl >= r || tr <= l)
		return 0;
	if (tl >= l && tr <= r) {
		int posX = lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin();
		int posY = --upper_bound(tree[v].begin(), tree[v].end(), y) - tree[v].begin();
		return posY - posX + 1;
	}
	int tm = (tl + tr) / 2;
	return get(v * 2, tl, tm, l, r, x, y) + get(v * 2 + 1, tm, tr, l, r, x, y);
}

int get(int l, int r, int x, int y) {
	return get(1, 0, n, l, r + 1, x, y);
}

void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	build(1, 0, n);
}

vector<int> ans;
void run() {
	for (int test = 0; test < q; test++) {
		int l, r, x, y;
		cin >> l >> r >> x >> y;
		l--;
		r--;
		int fans = get(l, r, x, y);
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
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