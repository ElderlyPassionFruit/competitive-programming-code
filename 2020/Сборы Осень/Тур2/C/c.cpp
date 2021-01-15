#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 2e9;


struct node{
	int val, pos, mod;
	node() {
		val = pos = mod = 0;
	}
};

node merge(const node & a, const node & b) {
	node ans;
	if (a.val > b.val) {
		ans.val = a.val;
		ans.pos = a.pos;
	}
	else {
		ans.val = b.val;
		ans.pos = b.pos;
	}
	ans.mod = 0;
	return ans;
}

struct segment_tree{
	vector<node> tree;
	int n;

	segment_tree() {}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			tree[v] = node();
			tree[v].pos = tl;
			tree[v].val = 0;
			tree[v].mod = 0;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
		tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(int sz) {
		n = sz;
		tree.resize(4 * n);
		build(1, 0, n);
	}

	void push(int v) {
		tree[v].val += tree[v].mod;
		tree[v * 2].mod += tree[v].mod;
		tree[v * 2 + 1].mod += tree[v].mod;
		tree[v].mod = 0;
	}

	node get_val(int v) {
		auto ans = tree[v];
		ans.val += ans.mod;
		ans.mod = 0;
		return ans;
	}

	void upd(int v, int tl, int tr, int l, int r, int val) {
		if (tl >= r || tr <= l) return;
		if (tl >= l && tr <= r) {
			tree[v].mod += val;
			return;
		} 
		int tm = (tl + tr) / 2;
		push(v);
		upd(v * 2, tl, tm, l, r, val);
		upd(v * 2 + 1, tm, tr, l, r, val);
		tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int l, int r, int x) {
		upd(1, 0, n, l, r + 1, x);

		//return;
		//for (int i = l; i <= r; i++)
		//	tree[i] += x;
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return node();
		if (tl >= l && tr <= r) return get_val(v);
		int tm = (tl + tr) / 2;
		push(v);
		return merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	pair<int, int> get(int l, int r) {
		node fans = get(1, 0, n, l, r + 1);
		if (fans.val == 0) return {0, n - 1};
		return {fans.val, fans.pos};

		//pair<int, int> ans = {0, n - 1};
		//for (int i = l; i <= r; i++)
		//	chkmax(ans, make_pair(tree[i], i));
		//return ans;
	}
};

struct segment{
	int l, r, ind;
	segment() {}
};

int n;
vector<segment> a;

void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].l >> a[i].r;
		a[i].r -= 5;
		a[i].ind = i;
	}
	vector<segment> help;
	for (auto i : a) {
		if (i.l <= i.r)
			help.push_back(i);
	}
	a = help;
	n = a.size();
	for (int i = 0; i < n; i++) {
		a[i].ind = i;
	}
}

vector<int> have;

int ans;
int f, s;

void make() {
	for (auto &i : a) {
		have.push_back(i.l);
		have.push_back(i.r);
	}
	have.push_back(1);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i.l = lower_bound(all(have), i.l) - have.begin();
		i.r = lower_bound(all(have), i.r) - have.begin();
	}
	have.push_back(2e9);
}

struct event{
	int x, type, ind;
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

segment_tree tree;
int now = 0;

void relax(int pos) {
	if (now > ans) {
		ans = now;
		f = pos;
		s = have.size() - 1;
	}
	int nxt = lower_bound(all(have), have[pos] + 5) - have.begin();
	auto fans = tree.get(nxt, have.size() - 1);
	if (now + fans.first > ans) {
		ans = now + fans.first;
		f = pos;
		s = fans.second;
	}
}
	

void run() {
	make();
	ans = -1;
	vector<event> q;
	tree = segment_tree(have.size());
	for (auto i : a) {
		if (i.l > i.r) continue;
		q.push_back({i.l, 1, i.ind});
		q.push_back({i.r + 1, 2, i.ind});
		tree.upd(i.l, i.r, 1);
	}
	sort(all(q));
	int l = 0, r = 0;
	while (l < q.size()) {
		while (r < q.size() && q[l].x == q[r].x){
			auto el = q[r];
			if (el.type == 1) {
				tree.upd(a[el.ind].l, a[el.ind].r, -1);
				now++;
			}
			else {
				now--;
			}
			r++;
		}
		relax(q[l].x);
		l = r;
	}
}

void write() {
	f = have[f];
	s = have[s];
	if (ans == -1) {
		ans = 0;
		f = 1;
		s = 10;
	}
	cout << ans << " " << f << " " << s << endl;
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