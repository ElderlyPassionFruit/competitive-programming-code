#include <bits/stdc++.h>

using namespace std;
#define int long long

int n;
const int MAXN = 1e5 + 10;
int a[MAXN], t[MAXN], pos[MAXN];
pair <int, int> tree[MAXN * 4];

void build(int v, int l, int r) {
	if (l == r - 1) {
		pos[l] = v;
		return;
	}
	int m = (l + r) / 2;
	build(v * 2, l, m);
	build(v * 2 + 1, m, r);
}

void upd(int p, pair <int, int> val) {
	int v = pos[p];
	tree[v] = max(val, tree[v]);
	v /= 2;
	while (v) {
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
		v /= 2;
	}
}

pair <int, int> get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return {0, 0};
	if (tl >= l && tr <= r) return tree[v];
	int tm = (tl + tr) / 2;
	return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
}

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> t[i];
}

int dp[MAXN];
int pred[MAXN];

int num;
vector<int> ans;

void get_ans(int pos) {
	if (pos == 0) return;
	ans.push_back(pos);
	get_ans(pred[pos]);
}

void run() {
	build(1, 0, MAXN);

	for (int i = 1; i <= n; i++) {
		auto h = get(1, 0, MAXN, 0, t[i]);
		dp[i] = h.first + a[i];
		pred[i] = h.second;
		upd(t[i], {dp[i], i});
	}

	pair <int, int> fans = {0, 0};

	for (int i = 1; i <= n; i++) {
		fans = max(fans, {dp[i], i});
	}

	num = fans.first;
	get_ans(fans.second);
	reverse(ans.begin(), ans.end());
}

void write() {
	cout << num << endl;
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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