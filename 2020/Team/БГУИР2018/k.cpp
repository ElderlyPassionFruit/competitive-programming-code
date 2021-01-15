#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
mt19937 rnd(time(0));

const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const int base1 = 228228 + rnd() % 1000 + 179;
const int base2 = 179179 + 1337 + rnd() % 228;

int add(int a, int b, int MOD) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b, int MOD) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b, int MOD) {
	return (ll)a * b % MOD;
}

const int MAXN = 2e5 + 10;
int pows1[MAXN], pows2[MAXN];

void build() {
	pows1[0] = 1;
	pows2[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows1[i] = mul(pows1[i - 1], base1, MOD1);
		pows2[i] = mul(pows2[i - 1], base2, MOD2);
	}
}

struct segment_tree{
	vector<pair<int, int>> tree;
	int n;
	segment_tree() {

	}
	segment_tree(int sz) {
		n = sz;
		tree.resize(n);
	}

	pair<int, int> get(int r) {
		pair<int, int> ans = {0, 0};
		for (;r >= 0; r = (r & (r + 1)) - 1) {
			ans.first = add(ans.first, tree[r].first, MOD1);
			ans.second = add(ans.second, tree[r].second, MOD2);
		}
		return ans;
	}

	pair<int, int> get(int l, int r) {
		pair<int, int> ans1 = get(r), ans2 = get(l - 1);
		ans1.first = sub(ans1.first, ans2.first, MOD1);
		ans1.second = sub(ans1.second, ans2.second, MOD2);
		return ans1;
		//int ans = 0;
		//for (int i = l; i <= r; i++)
		//;	ans = add(ans, tree[i]);
		//return ans;
	}

	void upd(int pos, int x, int y) {
		for (; pos < n; pos = (pos | (pos + 1))) {
			tree[pos].first = add(tree[pos].first, x, MOD1);
			tree[pos].second = add(tree[pos].second, y, MOD2);
		}
		//tree[pos] = add(x, tree[pos]);
	}
};

struct event{
	int x, y, y1, y2, ind, type;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y = b, ind = c, type = d;
	}
	event(int a, int b, int c, int d, int e) {
		x = a, y1 = b, y2 = c, ind = d, type = e;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

int n, m;
segment_tree tree;
vector<event> a;

void make() {
	vector<int> x, y;
	for (auto i : a) {
		x.push_back(i.x);
		if (i.type == 1) {
			y.push_back(i.y);
		}
		else {
			y.push_back(i.y1);
			y.push_back(i.y2);
		}
	}
	sort(all(x));
	x.resize(unique(all(x)) - x.begin());
	sort(all(y));
	y.resize(unique(all(y)) - y.begin());
	tree = segment_tree(y.size());
	for (auto &i : a) {
		i.x = lower_bound(all(x), i.x) - x.begin();
		if (i.type == 1) {
			i.y = lower_bound(all(y), i.y) - y.begin();
		}
		else {
			i.y1 = lower_bound(all(y), i.y1) - y.begin();
			i.y2 = lower_bound(all(y), i.y2) - y.begin();
		}
	}
}

vector<pair<int, int> > w;

void add_point(event a) {
	tree.upd(a.y, pows1[a.ind], pows2[a.ind]);
}

void add_wolf(event a) {
	auto x = tree.get(a.y1, a.y2);
	w[a.ind].first = sub(w[a.ind].first, x.first, MOD1);
	w[a.ind].second = sub(w[a.ind].second, x.second, MOD2);
}

void del_wolf(event a) {
	auto x = tree.get(a.y1, a.y2);
	w[a.ind].first = add(w[a.ind].first, x.first, MOD1);
	w[a.ind].second = add(w[a.ind].second, x.second, MOD2);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		a.push_back({x1, y1, y2, i, 0});
		a.push_back({x2, y1, y2, i, 2});
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		a.push_back({x, y, i, 1});
	}
	sort(all(a));
	w.resize(n);
	make();
	for (auto i : a) {
		if (i.type == 0)
			add_wolf(i);
		else if (i.type == 1)
			add_point(i);
		else
			del_wolf(i);
	}
	sort(all(w));
	w.resize(unique(all(w)) - w.begin());
	cout << w.size() << endl;
	return 0;
}













