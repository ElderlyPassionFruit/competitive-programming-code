#include <bits/stdc++.h>

using namespace std;
#define int long long

struct segment_tree
{
	int n;
	vector <int> tree, mod;

	segment_tree() {
		n = 0;
		tree = {};
		mod = {};
	}

	segment_tree(int sz) {
		n = sz;
		tree.assign(4 * n, 0);
		mod.assign(4 * n, 0);
	}	

	int get_val(int v) {
		return tree[v] + mod[v];
	}

	void push(int v) {
		mod[v * 2] += mod[v];
		mod[v * 2 + 1] += mod[v];
		mod[v] = 0;
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
		tree[v] = max(get_val(v * 2), get_val(v * 2 + 1));
	}

	void upd(int l, int r, int val) {
		upd(1, 0, n, l, r + 1, val);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return -1e9;
		if (tl >= l && tr <= r)
			return get_val(v);
		push(v);
		int tm = (tl + tr) / 2;
		int ans = max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		tree[v] = max(get_val(v * 2), get_val(v * 2 + 1));
		return ans;
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
	}
};

struct event{
	int type, x, y1, y2;
	event() {
		type = x = y1 = y2 = -1;
	}
	event(int a, int b, int c, int d) {
		type = a;
		x = b;
		y1 = c;
		y2 = d;
	}
};

bool cmp(event a, event b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.type < b.type;
}

vector <event> help;
int n;

void read() {
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		help.push_back({1, x1, y1, y2});
		help.push_back({-1, x2, y1, y2});
	}
	sort(help.begin(), help.end(), cmp);
}

int ans = 0;
void run() {
	set <int> fy;
	for (auto x : help) {
		fy.insert(x.y1);
		fy.insert(x.y2);
	}

	int cnt = 0;
	map <int, int> have;
	for (auto i : fy) {
		have[i] = cnt++;
	}

	segment_tree tree(cnt);
	
	for (auto i : help) {
		tree.upd(have[i.y1], have[i.y2], i.type);
		int a = tree.get(have[i.y1], have[i.y2]);
		//cout << a << endl;
		if (a == 1 && i.type == 1)
			ans++;
	}
}

void write() {
	cout << ans << endl;
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