#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct segmentTree{
	int n;
	vector<pair<int, int>> tree;
	vector<int> mod;

	segmentTree() {}

	void build(int v, int tl, int tr) {
		if (tl >= tr) return;
		if (tl == tr - 1) {
			tree[v] = {0, tl};
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	segmentTree(int _n) {
		n = _n;
		tree.assign(4 * n, {0, 0});
		mod.assign(4 * n, 0);
		build(1, 0, n);
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
	}

	pair<int, int> getVal(int v) {
		return {tree[v].first + mod[v], tree[v].second};
	}

	void upd(int v, int tl, int tr, int l, int r, int add) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			mod[v] += add;
			return;
		}
		push(v);
		int tm = (tl + tr) / 2;
		upd(v * 2, tl, tm, l, r, add);
		upd(v * 2 + 1, tm, tr, l, r, add);
		tree[v] = max(getVal(v * 2), getVal(v * 2 + 1));
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
		return;
		//for (int i = l; i <= r; i++) {
		//	tree[i] += val;
		//}
	} 

	pair<int, int> get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return {0, 0};
		if (tl >= l && tr <= r) return getVal(v);
		push(v);
		int tm = (tl + tr) / 2;
		auto ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		tree[v] = max(getVal(v * 2), getVal(v * 2 + 1));
		return ans;
	}

	pair<int, int> get(int r) {
		return get(1, 0, n, 0, r + 1);
		//pair<int, int> ans = {0, 0};
		//for (int i = 0; i <= r; i++) {
		//	ans = max(ans, make_pair(tree[i], i));
		//}
		//return ans;
	}
};

struct seg{
	int l, r, x, ind;
	seg() {}
	seg(int _l, int _r, int _x, int _ind) {
		l = _l, r = _r, x = _x, ind = _ind;
	}
};

int Unique(vector<seg> & a) {
	vector<int> have;
	for (auto [l, r, x, ind] : a) {
		have.push_back(l);
		have.push_back(r);
		have.push_back(x);
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &[l, r, x, ind] : a) {
		l = lower_bound(all(have), l) - have.begin();
		r = lower_bound(all(have), r) - have.begin();
		x = lower_bound(all(have), x) - have.begin();
	}
	return have.size();
}

struct event{
	int l, r, add;
	event() {}
	event(int _l, int _r, int _add) {
		l = _l, r = _r, add = _add;
	}
};

int n;
vector<seg> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	a.resize(n);
	int it = 0;
	for (auto &i : a) {
		cin >> i.l >> i.x >> i.r;
		a[it].ind = it;
		it++;
	}
	int sz = Unique(a);
	vector<vector<event>> have(sz + 1);
	for (auto [l, r, x, ind] : a) {
		have[x].push_back({l, x, 1});
		have[r + 1].push_back({l, x, -1});
	}
	pair<int, pair<int, int>> ans = {0, {0, 0}};
	segmentTree tree(sz + 1);
	for (int i = 0; i <= sz; i++) {
		for (auto [l, r, add] : have[i]) {
			tree.upd(l, r, add);
		}
		auto now = tree.get(i);
		ans = max(ans, make_pair(now.first, make_pair(now.second, i)));
		/*cout << "tree = " << endl;
		for (auto i : tree.tree) {
			cout << i << " ";
		}
		cout << endl;*/
	}
	/*cout << "a = " << endl;
	for (auto i : a) {
		cout << i.l << " " << i.x << " " << i.r << " " << i.ind << endl;
	}*/
	vector<int> fans;
	for (auto [l, r, x, ind] : a) {
		if (l <= ans.second.first && ans.second.second <= r && ans.second.first <= x && ans.second.second >= x) {
			fans.push_back(ind);
		}
	}
	//cout << "ans = " << ans.first << " " << ans.second.first << " " << ans.second.second << endl;
	sort(all(fans));
	fans.resize(unique(all(fans)) - fans.begin());
	cout << fans.size() << endl;
	for (auto i : fans) {
		cout << i + 1 << " ";
	}
	cout << endl;
	//assert(fans.size() == ans.first);
	
	return 0;
}