#include <bits/stdc++.h>

using namespace std;

struct get_max{
	vector<int> tree, mod, a;
	int n;

	get_max() {
		tree = {};
		mod = {};
		a = {};
		n = 0;
	}

	void build(int v, int l, int r) {
		mod[v] = 0;
		if (l == r - 1) {
			tree[v] = a[l];
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	get_max(vector<int> arr) {
		a = arr;
		n = arr.size();
		mod.assign(n * 4, 0);
		tree.assign(n * 4, 0);
		build(1, 0, n);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
	}

	int get_ans(int v) {
		return tree[v] + mod[v];
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return get_ans(v);
		push(v);
		int tm = (tl + tr) / 2;
		int ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		tree[v] = max(get_ans(v * 2), get_ans(v * 2 + 1));
		return ans;
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}

	void upd(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return;
		if (tl >= l && tr <= r) {
			mod[v]--;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r);
		upd(v * 2 + 1, tm, tr, l, r);
		tree[v] = max(get_ans(v * 2), get_ans(v * 2 + 1));
	} 

	void upd(int l, int r) {
		upd(1, 0, n, l, r + 1);
	}
};

int n, q;

vector<int> arr;
get_max help;
void read() {
	cin >> n >> q;
	arr.resize(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	help = get_max(arr);
}

void add(int l, int r, int diff) {
	help.upd(l, r);
}

int solve(int l, int r, int x) {
	for (int i = l; i <= r; i++) {
		int fx = help.get(i, i);
		if (fx > 1) {
			x /= fx;
			if (x == 0) {
				return i + 1;
			}	
			continue;
		}
		if (help.get(i, r) <= 1)
			break;

		int l1 = i, r1 = r;

		if (help.get(i, min(i + 100, r)) > 1)
			r1 = min(i + 100, r);

		if (help.get(i, max(i, r - 100)) <= 1)
			l1 = max(i, r - 100);

		while (l1 < r1 - 1) {
			int mid = (l1 + r1) / 2;
			if (help.get(i, mid) <= 1)
				l1 = mid;
			else
				r1 = mid;
		}
		i = l1;
	}
	return -1;
}

const int MAXN = 5 * 1e5 + 10;
int ans[MAXN];

int cnt = 0;
void run() {
	for (int test = 0; test < q; test++) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			add(l, r, -1);
		}
		else if (type == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			r--;
			ans[cnt++] = solve(l, r, x);
		}
	}
}

void write() {
	for (int i = 0; i < cnt; i++) {
		cout << ans[i] << " ";
	}
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}