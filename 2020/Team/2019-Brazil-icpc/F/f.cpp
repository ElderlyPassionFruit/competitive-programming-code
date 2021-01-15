#include <bits/stdc++.h>

using namespace std;
#define all(x) x.begin(), x.end()
using ll = long long;

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct node{
	int min;
	int mod;
	int sum;
	node() {
		min = 0, sum = 1, mod = 0;
	}
	node(int a, int b) {
		min = a, sum = b, mod = 0;
	}
};

node merge(const node & a, const node & b) {
	node ans;
	if (a.min < b.min)
		ans = a;
	else if (a.min > b.min)
		ans = b;
	else
		ans = node(a.min, a.sum + b.sum);
	return ans;
}

const int MAXN = 2e4 + 228;

node tree[MAXN * 4];
int treeN;

void build(int v, int tl, int tr, vector<int> & a) {
	if (tr >= tl) return;
	if (tl == tr - 1) {
		tree[v] = node(0, a[tl]);
		return;
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm, a);
	build(v * 2 + 1, tm, tr, a);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void init(vector<int> & a) {
	treeN = a.size();
	build(1, 0, treeN, a);
}

void push(int v) {
	tree[v * 2].mod += tree[v].mod;
	tree[v * 2 + 1].mod += tree[v].mod;
	tree[v].mod = 0;
}

node get_val(int v) {
	return node(tree[v].min + tree[v].mod, tree[v].sum);
}

node get() {
	return get_val(1);
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

void upd(int l, int r, int val) {
	upd(1, 0, treeN, l, r, val);
}

struct event{
	int x, y1, y2, type;
	event() {}
	event(int a, int b, int c, int d) {
		x = a, y1 = b, y2 = c, type = d;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

int n;
event a[MAXN];
int topA;
vector<int> have;
int rects[MAXN][4], frects[MAXN][4];

ll solve() {
	topA = 0;
	for (int i = 0; i < n; i++) {
		int x1 = frects[i][0], y1 = frects[i][1], x2 = frects[i][2], y2 = frects[i][3];
		a[topA++] = {x1, y1, y2, 1};
		a[topA++] = {x2, y1, y2, -1};
	}
	have.clear();
	for (int i = 0; i < topA; i++) {
		have.push_back(a[i].y1);
		have.push_back(a[i].y2);
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	assert(!have.empty());
	for (int i = 0; i < topA; i++) {
		a[i].y1 = lower_bound(all(have), a[i].y1) - have.begin();
		a[i].y2 = lower_bound(all(have), a[i].y2) - have.begin();
	}
	int full = have.back() - have[0];
	for (int i = (int)have.size() - 1; i >= 1; i--) {
		have[i] = have[i] - have[i - 1];
	}
	//cerr << "good = " << endl;
	have.erase(have.begin());
	/*cerr << "have = " << endl;
	for (auto i : have) {
		cerr << i << " ";
	}
	cerr << endl;*/
	init(have);
	//cerr << "good =" << endl;
	ll ans = 0;
	sort(a, a + topA);
	int last = a[0].x;
	int l = 0, r = 0;
	while (l < topA) {
		auto fans = get();
		int len = full;
		if (fans.min == 0) {
			len -= fans.sum;
		}
		ans += (ll)len * (a[l].x - last);
		last = a[l].x;
		while (r < topA && a[l].x == a[r].x) {
			upd(a[r].y1, a[r].y2, a[r].type);
			r++;
		}
		l = r;
	}
	return ans;
}


void make(int ind, int r, int x1, int y1, int x2, int y2) {
	frects[ind][0] = max(x1, rects[ind][0] - r);
	frects[ind][1] = max(y1, rects[ind][1] - r);
	frects[ind][2] = min(x2, rects[ind][2] + r);
	frects[ind][3] = min(y2, rects[ind][3] + r);
}

ll get(int x1, int y1, int x2, int y2, int r) {
	for (int i = 0; i < n; i++) {
		make(i, r, x1, y1, x2, y2);
	}
	return solve();
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	//n = 10000;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> rects[i][j];
			//rects[i][j] = get(0, 100000);
		}
	//	if (rects[i][0] > rects[i][2]) swap(rects[i][0], rects[i][2]);
	//	if (rects[i][1] > rects[i][3]) swap(rects[i][1], rects[i][3]);
	}
	int p;
	cin >> p;
	//p = get(1, 100);
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	//x1 = 0, y1 = 0, x2 = 100000, y2 = 100000;
	//if (x1 > x2) swap(x1, x2);
	//if (y1 > y2) swap(y1, y2);

	int l = -1, r = 1e9;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (get(x1, y1, x2, y2, mid) * 100 >= (ll)p * (x2 - x1) * (y2 - y1)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << r << endl;
	return 0;
}