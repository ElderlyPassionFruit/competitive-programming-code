#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

struct segment_tree {
	vector <int> tree_max, mod, pos;
	vector <pair <int, int> > tree_min;
	int n;

	void build(int v, int l, int r) {
		if (l == r - 1) {
			tree_min[v] = { 0, l };
			pos[l] = v;
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		tree_min[v] = min(tree_min[v * 2], tree_min[v * 2 + 1]);
	}

	segment_tree() {
		n = 0;
		tree_min = {};
		tree_max = {};
		mod = {};
	}

	segment_tree(int sz) {
		n = sz + 1;
		tree_min.assign(n * 4, {0, 0});
		tree_max.assign(n * 4, 0);
		mod.assign(n * 4, 0);
		pos.assign(n, 0);
		build(1, 0, n);
	}



	void push(int v) {
		mod[v * 2 + 1] += mod[v];
		mod[v * 2] += mod[v];
		mod[v] = 0;
	}

	pair <int, int> get_val_min(int v) {
		return { tree_min[v].first + mod[v], tree_min[v].second };
	}

	int get_val_max(int v) {
		return tree_max[v] + mod[v]; 
	}


	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return;
		if (tl >= l && tr <= r) {
			mod[v] += val;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree_min[v] = min(get_val_min(v * 2), get_val_min(v * 2 + 1));
		tree_max[v] = max(get_val_max(v * 2), get_val_max(v * 2 + 1));
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return -1e9;
		if (tl >= l && tr <= r) {
			return get_val_max(v);
		}
		push(v);
		int tm = (tl + tr) / 2;
		int ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		tree_min[v] = min(get_val_min(v * 2), get_val_min(v * 2 + 1));
		tree_max[v] = max(get_val_max(v * 2), get_val_max(v * 2 + 1));
		return ans;
	}


	void set_val(int p) {
		/*int v = pos[p];
		tree_max[v] = 0;
		tree_min[v] = { 0, p };
		mod[v] = 0;
		v /= 2;
		while (v) {
			tree_min[v] = min(get_val_min(v * 2), get_val_min(v * 2 + 1));
			tree_max[v] = max(get_val_max(v * 2), get_val_max(v * 2 + 1));
			v /= 2;
		}*/
		
		int help = get(1, 0, n, p, p + 1);
		upd(1, 0, n, p, p + 1, -help);
	}

	int first_left(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return 1e9;
		if (get_val_min(v).first > val)
			return 1e9;
		if (tl == tr - 1)
			return get_val_min(v).second;
		push(v);
		int tm = (tl + tr) / 2;
		tree_min[v] = min(get_val_min(v * 2), get_val_min(v * 2 + 1));
		tree_max[v] = max(get_val_max(v * 2), get_val_max(v * 2 + 1));
		//int ans = min(first_left(v * 2, tl, tm, l, r, val), first_left(v * 2 + 1, tm, tr, l, r, val));
		int ans = first_left(v * 2, tl, tm, l, r, val);
		if (ans == 1e9)
			ans = first_left(v * 2 + 1, tm, tr, l, r, val);
		return ans;
	}

	int first_right(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l)
			return -1e9;
		if (get_val_min(v).first > val)
			return -1e9;
		if (tl == tr - 1)
			return get_val_min(v).second;
		push(v);
		int tm = (tl + tr) / 2;
		tree_min[v] = min(get_val_min(v * 2), get_val_min(v * 2 + 1));
		tree_max[v] = max(get_val_max(v * 2), get_val_max(v * 2 + 1));
		
		//int ans = max(first_right(v * 2, tl, tm, l, r, val), first_right(v * 2 + 1, tm, tr, l, r, val));
		int ans = first_right(v * 2 + 1, tm, tr, l, r, val);
		if (ans == 1e9)
			ans = first_right(v * 2, tl, tm, l, r, val);
		return ans;
	}

	int get(int p) {
		int v = pos[p];
		int ans = get_val_max(v);
		v /= 2;
		while (v) {
			ans += mod[v];
			v /= 2;
		}
		return ans;
	}
}; 

struct help_struct {
	vector <int> arr;
	segment_tree tree;
	int n;
	help_struct() {
		arr = {};
		tree = {};
		n = 0;
	}

	help_struct(int sz) {
		arr.assign(sz + 10, 0);
		tree = segment_tree(sz);
		n = sz;
	}

	int get(int l, int r) {
		int mx = -1e9;
		mx = tree.get(1, 0, tree.n, l, r + 1);
		return mx;
	}

	void upd(int l, int r, int val) {
		tree.upd(1, 0, tree.n, l, r + 1, val);
	}

	void add() {
		upd(1, n, 1);
	}

	void make_zero(int pos) {
		tree.set_val(pos);
	}

	int first_left(int pos, int val) {
		int ans = tree.first_left(1, 0, tree.n, pos, tree.n , val);
		if (ans == 1e9)
			ans = -1;
		return ans;
	}

	int first_right(int pos, int val) {
		int ans = tree.first_right(1, 0, tree.n, 1, pos, val);
		if (ans == -1e9)
			ans = -1;
		return ans;
	}

	int val(int pos) {
		return tree.get(pos);
	}
};


int n, m, q;

help_struct h, w;
void read() {
	cin >> n >> m >> q;
	h = help_struct(n);
	w = help_struct(m);
}

void del_r(int r) {
	h.make_zero(r);
}

void del_c(int c) {
	w.make_zero(c);
}

void add() {
	h.add();
	w.add();
}

int fans(int r1, int c1, int r2, int c2, int k) {
	int f1 = h.val(r1);
	int f2 = w.val(c1);
	int f3 = h.val(r2);
	int f4 = w.val(c2);

	if ((f1 > k && f2 > k) || (f3 > k && f4 > k))
		return -1;
	if (r1 > r2) {
		swap(r1, r2);
		swap(c1, c2);
	}

	int help_h, help_w;

	help_h = h.get(r1, r2);
	help_w = w.get(min(c1, c2), max(c1, c2));

	if (min(help_h, help_w) <= k)
		return abs(r1 - r2) + abs(c1 - c2);

	if ((h.val(r1) <= k && w.val(c2) <= k) || (h.val(r2) <= k && w.val(c1) <= k)) {
		return abs(r1 - r2) + abs(c1 - c2);
	}

	int ans = 1e9;

	int v1 = h.val(r1);
	int v2 = h.val(r2);

	if (v1 <= k && v2 <= k) {
		int pos1_1 = w.first_left(c1, k);
		int pos1_2 = w.first_right(c1, k);
		int pos2_1 = w.first_left(c2, k);
		int pos2_2 = w.first_right(c2, k);

		int fans = 1e9;
		if (pos1_1 != -1) {
			fans = min(fans, abs(r1 - r2) + abs(pos1_1 - c1) + abs(pos1_1 - c2));
		}

		if (pos1_2 != -1) {
			fans = min(fans, abs(r1 - r2) + abs(pos1_2 - c1) + abs(pos1_2 - c2));
		}

		if (pos2_1 != -1) {
			fans = min(fans, abs(r1 - r2) + abs(pos2_1 - c1) + abs(pos2_1 - c2));
		}

		if (pos2_2 != -1) {
			fans = min(fans, abs(r1 - r2) + abs(pos2_2 - c1) + abs(pos2_2 - c2));
		}

		ans = min(ans, fans);
	}

	v1 = w.val(c1);
	v2 = w.val(c2);

	if (v1 <= k && v2 <= k) {
		int pos1_1 = h.first_left(r1, k);
		int pos1_2 = h.first_right(r1, k);
		int pos2_1 = h.first_left(r2, k);
		int pos2_2 = h.first_right(r2, k);

		int fans = 1e9;
		if (pos1_1 != -1) {
			fans = min(fans, abs(c1 - c2) + abs(r1 - pos1_1) + abs(r2 - pos1_1));
		}

		if (pos1_2 != -1) {
			fans = min(fans, abs(c1 - c2) + abs(r1 - pos1_2) + abs(r2 - pos1_2));
		}

		if (pos2_2 != -1) {
			fans = min(fans, abs(c1 - c2) + abs(r1 - pos2_2) + abs(r2 - pos2_2));
		}

		if (pos2_1 != -1) {
			fans = min(fans, abs(c1 - c2) + abs(r1 - pos2_1) + abs(r2 - pos2_1));
		}
		ans = min(ans, fans);
	}
	if (ans == 1e9)
		ans = -1;
	return ans;
}

vector <int> ans;

void run() {
	for (int test = 0; test < q; test++) {
		add();
		int type;
		cin >> type;
		if (type == 1) {
			int r;
			cin >> r;
			del_r(r);
		}
		if (type == 2) {
			int c;
			cin >> c;
			del_c(c);
		}
		if (type == 3) {
			int r1, c1, r2, c2, k;
			cin >> r1 >> c1 >> r2 >> c2 >> k;
			int ax;
			ax = fans(r1, c1, r2, c2, k);
			cout << ax << '\n';
		}
	}
}

void write() {

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