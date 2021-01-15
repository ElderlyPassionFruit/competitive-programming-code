#include <bits/stdc++.h>

using namespace std;
//#define int long long
struct segment_tree {
	vector <int> tree;
	vector <int> pos;
	int n;
	segment_tree() {
		n = 0;
		tree = {};
		pos = {};
	}

	segment_tree(int x) {
		n = x;
		tree.assign(4 * n, 0);
		pos.assign(n, 0);
	}

	void build(int v, int l, int r) {
		if (l == r - 1) {
			pos[l] = v;
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
	}

	void build() {
		tree.assign(4 * n, 0);
	}

	void set_val(int p, int val) {
		int v = pos[p];
		tree[v] = val;
		v /= 2;
		while (v) {
			tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l) return 0;
		if (tl >= l && tr <= r) return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r);
	}
};

const int MAXN = 1e4 + 10;
int arr[MAXN];
int n, m;
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

vector <int> ans;

void run() {
	vector <pair <int, int> > ev;
	vector <int> help(m + n);
	for (int test = 0; test < m; test++) {
		int a, b;
		cin >> a >> b;
		a--;
		help[test] = b;
		ev.push_back({a, b});
	}
	for (int i = 0; i < n; i++) {
		help[m + i] = arr[i];
	}
	sort(help.begin(), help.end());
	unordered_map <int, int> pos;
	int p = 0;
	pos[help[0]] = p++;
	for (int i = 1; i < help.size(); i++) {
		if (help[i] == help[i - 1]) continue;
		pos[help[i]] = p++;
	}
	segment_tree segment(help.size());
	segment.build(1, 0, help.size());
	for (int test = 0; test < m; test++) {
		int a = ev[test].first, b = ev[test].second;
		int now = arr[a];
		arr[a] = b;
		segment.build();

		for (int i = 0; i < n; i++) {
			int g = segment.get(0, pos[arr[i]]);
			segment.set_val(pos[arr[i]], g + 1);
		}
		ans.push_back(segment.tree[1]);
		arr[a] = now;
	}
}

void write() {
	for (auto i : ans) {
		cout << i << '\n';
	}
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