#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
int mod[MAXN * 8];
pair <int, int> tree[MAXN * 8];


pair <int, int> get_val(int v) {
	return make_pair(tree[v].first + mod[v], tree[v].second);
}

void merge(int v) {
	tree[v] = max(get_val(v * 2), get_val(v * 2 + 1)); 
}

void push(int v) {
	mod[v * 2] += mod[v];
	mod[v * 2 + 1] += mod[v];
	tree[v].first += mod[v];
	mod[v] = 0;
}

void build(int v, int tl, int tr) {
	if (tl == tr - 1) {
		tree[v].second = tl;
		return;
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm, tr);
	merge(v);
}

void upd(int v, int tl, int tr, int l, int r, int val) {
	if (tl >= r || tr <= l) {
		return;
	}
	if (tl >= l && tr <= r) {
		mod[v] += val;
		return;
	}
	push(v);
	int tm = (tl + tr) / 2;
	upd(v * 2, tl, tm, l, r, val);
	upd(v * 2 + 1, tm, tr, l, r, val);
	merge(v);
}


struct event{
	int x, y1, y2, t;
	event(int a, int b, int c, int d) {
		x = a, y1 = b, y2 = c, t = d;
	}
};

bool cmp(event & a, event & b) {
	return a.x < b.x || (a.x == b.x && a.t > b.t);
}

int n;
vector<event> a;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1 += MAXN;
		y1 += MAXN;
		x2 += MAXN;
		y2 += MAXN;
		a.push_back({x1, y1, y2, 1});
		a.push_back({x2, y1, y2, -1});
	}
	sort(a.begin(), a.end(), cmp);
	build(1, 0, 2 * MAXN);
}

int ans = -1e9;
pair <int, int> fans;

void run() {
	for (int i = 0; i < n * 2; i++) {
		upd(1, 0, 2 * MAXN, a[i].y1, a[i].y2 + 1, a[i].t);
		auto check = get_val(1);
		if (check.first > ans) {
			ans = check.first;
			fans = {a[i].x, check.second};
		}
	}
}

void write() {
	cout << ans << endl;
	cout << fans.first - MAXN << " " << fans.second - MAXN << endl;
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