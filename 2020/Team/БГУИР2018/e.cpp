#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int a, int b) {
		x = a, y = b;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct node{
	int cnt;
	pt a, b;
	node() {}
};

node merge(node a, node b) {
	node ans;
	ans.cnt = a.cnt + b.cnt;
	if (a.cnt >= 2) {
		ans.a = a.a;
		ans.b = a.b;
	}
	else if (a.cnt == 1 && b.cnt >= 1) {
		ans.a = a.a;
		ans.b = b.a;
	}
	else if (b.cnt >= 2) {
		ans.a = b.a;
		ans.b = b.b;
	}
	else if (b.cnt >= 1) {
		ans.a = b.a;
	}
	return ans;
}

struct segment_tree{
	int n;
	vector<node> tree;
	vector<set<pt>> leaves;  
	vector<int> pos;
	segment_tree() {

	}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segment_tree(int sz) {
		n = sz;
		tree.resize(4 * n);
		pos.resize(4 * n);
		leaves.resize(n);
	}

	void add(int p, pt a) {
		int v = pos[p];
		tree[v].cnt++;
		if (tree[v].cnt == 1)
			tree[v].a = a;
		else {
			tree[v].a = *leaves[p].begin();
			tree[v].b = a;
		}
		leaves[p].insert(a);
		v /= 2;
		while (v) {
			tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	void del(int p, pt a) {
		int v = pos[p];
		tree[v].cnt--;
		leaves[p].erase(a);
		if (tree[v].cnt == 1) {
			tree[v].a = *leaves[p].begin();
		}
		else if (tree[v].cnt >= 2) {
			tree[v].a = *leaves[p].begin();
			cout << "sz = " << leaves[p].size() << endl;
			cout << 1 << endl;
			auto it = leaves[p].begin();
			++it;
			tree[v].b = *(it);
			cout << 2 << endl;
		}
		v /= 2;
		while (v) {
			tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return node();
		if (tl >= l && tr <= r) 
			return tree[v];
		int tm = (tl + tr) / 2;
		return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	node get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

struct event{
	int x, y, type, ind;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y = b, type = c, ind = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

int n;
vector<pt> p;
vector<event> a;
vector<int> y;
segment_tree tree;

void build() {
	y.clear();
	for (auto i : a) {
		y.push_back(i.y);
	}
	sort(all(y));
	y.resize(unique(all(y)) - y.begin());
	tree = segment_tree(y.size());
}

vector<vector<pt> > have;
vector<bool> used;

bool check(pt a, pt b, pt c, int s) {
	if (max(a.x, max(b.x, c.x)) - min(a.x, min(b.x, c.x)) > s) return false;
	if (max(a.y, max(b.y, c.y)) - min(a.y, min(b.y, c.y)) > s) return false;
	return true;
}

bool check(int s) {
	a.clear();
	used.assign(n, false);
	have.assign(n, {});
	for (int i = 0; i < n; i++) {
		a.push_back({p[i].x, p[i].y, 0, i});
		a.push_back({p[i].x + s, p[i].y, 1, i});
	}
	sort(all(a));
	cout << "a = " << endl;
	for (auto i : a)
		cout << i.x << " " << i.y << " " << i.ind << " " << i.type << endl;
	cout << endl;
	build();
	for (int i = 0; i < a.size(); i++) {
		int j = i;
		while (j < a.size() && a[i].x == a[j].x && a[j].type == 0)
			j++;		
		cout << "puhh" << endl;
		// Добавление точек лежащих на одном x
		for (int k = i; k < j; k++) {
			int pos = lower_bound(all(y), a[k].y) - y.begin();
			tree.add(pos, {a[k].x, a[k].y});
		}

		cout << "puhh" << endl;
		for (int k = i; k < j; k++) {
			int pos = lower_bound(all(y), a[k].y) - y.begin();
			tree.add(pos, {a[k].x, a[k].y});

			int l = lower_bound(all(y), a[k].y - s) - y.begin();
			int r = --upper_bound(all(y), a[k].y + s) - y.begin();
			node get = tree.get(l, r);
			if (get.cnt >= 3) {
				used[a[k].ind] = true;
			}
			else {
				if (get.cnt == 1) {
					have[a[k].ind].push_back(get.a);
				}
				if (get.cnt == 2) {
					have[a[k].ind].push_back(get.a);
					have[a[k].ind].push_back(get.b);
				}
			}
			tree.del(pos, {a[k].x, a[k].y});
		}


		cout << "puhh" << endl;

		int l = j;
		while (l < a.size() && a[l].x == a[i].x && a[l].type == 1) {
			l++;
		}

		for (int k = j; k < l; k++) {
			int pos = lower_bound(all(y), a[k].y) - y.begin();
			tree.del(pos, {a[k].x, a[k].y});
		}
		i = l - 1;
	}
	reverse(all(a));
	tree = segment_tree(y.size());
	for (int i = 0; i < a.size(); i++) {
		int j = i;
		while (j < a.size() && a[i].x == a[j].x && a[j].type == 0)
			j++;
		
		for (int k = i; k < j; k++) {
			int l = lower_bound(all(y), a[k].y - s) - y.begin();
			int r = --upper_bound(all(y), a[k].y + s) - y.begin();
			node get = tree.get(l, r);
			if (get.cnt >= 3) {
				used[a[k].ind] = true;
			}
			else {
				if (get.cnt == 1) {
					have[a[k].ind].push_back(get.a);
				}
				if (get.cnt == 2) {
					have[a[k].ind].push_back(get.a);
					have[a[k].ind].push_back(get.b);
				}
			}
		}

		// Добавление точек лежащих на одном x
		for (int k = i; k < j; k++) {
			int pos = lower_bound(all(y), a[k].y) - y.begin();
			tree.add(pos, {a[k].x, a[k].y});
		}

		int l = j;
		while (l < a.size() && a[l].x == a[i].x && a[l].type == 1) {
			l++;
		}

		for (int k = j; k < l; k++) {
			int pos = lower_bound(all(y), a[k].y) - y.begin();
			tree.del(pos, {a[k].x, a[k].y});
		}
		i = l - 1;
	}

	cout << "puhh" << endl;

	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		if (have[i].size() < 2) continue;
		vector<int> P(have[i].size());
		P[P.size() - 1] = 1;
		P[P.size() - 2] = 1;
		do {
			vector<pt> kek;
			for (int j = 0; j < (int)P.size(); j++) {
				if (P[j])
					kek.push_back(have[i][j]);
			}
			kek.push_back(p[i]);
			if (check(kek[0], kek[1], kek[2], s)) {
				used[i] = true;
				break;
			}
		} while (next_permutation(all(P)));
	}

	for (auto i : used)
		if (!i)
			return false;
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	p.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	//cout << "puhh" << endl;
	int l = 0, r = 2e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}















