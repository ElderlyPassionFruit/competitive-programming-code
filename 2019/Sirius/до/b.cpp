#include <bits/stdc++.h>

using namespace std;
#define int long long

int n, m;
const int MAXN = 1e5 + 10;
int arr[MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

const int INF = -1e18;

struct node{
	int dp[2][2];
	int ans;
	node() {
		ans = dp[0][0] = dp[0][1] = dp[1][0] = dp[1][1] = 0;
	}
	node(int x) {
		ans = x;
		dp[0][0] = 0;
		dp[1][0] = INF;
		dp[0][1] = INF;
		dp[1][1] = x;
	}
};

node tree[MAXN * 4];

bool check(int r, int l) {
	if (r == 1 && l == 1) {
		return false;
	}
	else {
		return true;
	}
}

node merge(node a, node b) {
	node ans;
	for (int ai = 0; ai < 2; ai++) {
		for (int aj = 0; aj < 2; aj++) {
			for (int bi = 0; bi < 2; bi++) {
				for (int bj = 0; bj < 2; bj++) {
					if (check(aj, bi)) {
						ans.dp[ai][bj] = max(ans.dp[ai][bj], a.dp[ai][aj] + b.dp[bi][bj]);
						ans.ans = max(ans.ans, ans.dp[ai][bj]);
					}
				}
			}
		}
	}
	return ans;
}

void build(int v, int l, int r) {
	if (l == r - 1) {
		tree[v] = node(arr[l]);
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void update(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l)
		return;
	if (tl == l && tr == r) {
		tree[v] = node(val);
		return;
	}
	int tm = (tl + tr) / 2;
	update(v * 2, tl, tm, l, r, val);
	update(v * 2 + 1, tm, tr, l, r, val);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l)
		return INF;
	if (tl >= l && tr <= r)
		return tree[v];
	int tm = (tl + tr) / 2;
	node ans = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	return ans;
}

vector <int> ans;
void run() {
	build(1, 0, n);
	ans.push_back(get(1, 0, n, 0, n).ans);
	for (int test = 0; test < m; test++) {
		int b, t;
		cin >> b >> t;
		b--;
		update(1, 0, n, b, b + 1, t);
		node ax = get(1, 0, n, 0, n);
		ans.push_back(ax.ans);
	}
}

void write() {
	for (auto i : ans) {
		cout << i << endl;
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