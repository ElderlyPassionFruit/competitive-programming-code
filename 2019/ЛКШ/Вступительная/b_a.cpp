#include <bits/stdc++.h>

using namespace std;
#define int long long

struct segment_tree
{
	vector <int> tree_max;
	vector <int> tree_sum;
	vector <int> pos;
	vector <pair <int, int> > arr;
	int n;

	int dist(const pair <int, int> & a, const pair <int, int> & b) {
		return abs(a.first - b.first) + abs(a.second - b.second);
	}

	segment_tree() {
		n = 0;
		arr = {};
		tree_sum = {};
		tree_max = {};
		pos = {};
	}

	void write() {
		cout << endl;
		cout << "arr = " << endl;
		for (int i = 1; i < n; i++)
			cout << arr[i].first << " " << arr[i].second << endl; 
		cout << "tree_sum = " << endl;
		for (int i = 1; i < n; i++) {
			cout << tree_sum[pos[i]] << " ";
		} 
		cout << endl;
		cout << "tree_max = " << endl;
		for (int i = 1; i < n; i++) {
			cout << tree_max[pos[i]] << " ";
		} 
		cout << endl;
	}

	void build(int v, int l, int r) {
		if (l == r - 1) {
			pos[l] = v;
			int val = dist(arr[l], arr[l + 1]);
			tree_sum[v] = val;

			if (l < 1)
				return;
			int val2 = dist(arr[l], arr[l - 1]);			
			int val3 = dist(arr[l - 1], arr[l + 1]);
			tree_max[v] = val + val2 - val3;
			return;
		}

		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);

		tree_sum[v] = tree_sum[v * 2] + tree_sum[v * 2 + 1];
		tree_max[v] = max(tree_max[v * 2], tree_max[v * 2 + 1]);
	}

	void build() {
		build(1, 0, n);
		/*for (int i = 1; i < n - 1; i++) {
			int val = dist(arr[i], arr[i + 1]);
			tree_sum[i] = val;
			val += dist(arr[i - 1], arr[i]) - dist(arr[i - 1], arr[i + 1]);
			if (i > 1)
			tree_max[i] = val;
		}*/
	}

	segment_tree(vector <pair <int, int> > a) {
		n = a.size();
		arr = a;
		arr.push_back({0, 0});
		tree_max.assign(4 * n, 0);
		tree_sum.assign(4 * n, 0);
		pos.assign(n, 0);
		build();
	}

	void upd_sum(int p) {
		int v = pos[p];
		tree_sum[v] = dist(arr[p], arr[p + 1]);
		v /= 2;
		while (v) {
			tree_sum[v] = tree_sum[v * 2] + tree_sum[v * 2 + 1];
			v /= 2;
		}
	}

	void relax_sum(int pos) {
		if (pos >= n - 1)
			return;
		upd_sum(pos);
		//tree_sum[pos] = dist(arr[pos], arr[pos + 1]);
	}

	void upd_max(int p) {
		int v = pos[p];
		tree_max[v] = dist(arr[p - 1], arr[p]) + dist(arr[p], arr[p + 1]) - dist(arr[p - 1], arr[p + 1]);
		v /= 2;
		while (v) {
			tree_max[v] = max(tree_max[v * 2], tree_max[v * 2 + 1]);
			v /= 2;
		}
	}

	void relax_max(int pos) {
		if (pos >= n - 2 || pos < 2)
			return;
		upd_max(pos);
		//tree_max[pos] = tree_sum[pos - 1] + tree_sum[pos] - dist(arr[pos - 1], arr[pos + 1]);
	}

	void upd(int pos, int x, int y) {
		arr[pos] = {x, y};
		relax_sum(pos - 1);
		relax_sum(pos);
		relax_max(pos - 1);
		relax_max(pos);
		relax_max(pos + 1);
	}

	int get_sum(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return tree_sum[v];
		int tm = (tl + tr) / 2;
		return get_sum(v * 2, tl, tm, l, r) + get_sum(v * 2 + 1, tm, tr, l, r);
	}

	int get_max(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return tree_max[v];
		int tm = (tl + tr) / 2;
		return max(get_max(v * 2, tl, tm, l, r), get_max(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		int ans = 0;
		/*for (int i = l; i < r; i++) {
			ans += tree_sum[i];
		}
		*/
		ans = get_sum(1, 0, n, l, r);

		int mx = get_max(1, 0, n, l + 1, r);
	//	cout << "l = " << l << " r = " << r << endl;
	//	cout << "ans = " << ans << " mx = " << mx << endl;
	/*	for (int i = l + 1; i < r; i++)
			mx = max(mx, tree_max[i]);
	*/
		ans -= mx;
		return ans;
	}
};

int n, q;
vector <pair <int, int> > arr;
void read() {
	cin >> n >> q;
	arr.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}
}

vector <int> ans;
segment_tree tree;
void run() {
	tree = segment_tree(arr);
	//tree.write();
	for (int test = 0; test < q; test++) {
		char type;
		cin >> type;
		if (type == 'Q') {
			int l, r;
			cin >> l >> r;
			int ax = tree.get(l, r);
		//	cout << ax << endl;
			ans.push_back(ax);
		}
		else if (type == 'U') {
			int k, x, y;
			cin >> k >> x >> y;
			tree.upd(k, x, y);
		}
	//	cout << endl;
	//	cout << "test = " << test + 1;
	//	tree.write();
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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