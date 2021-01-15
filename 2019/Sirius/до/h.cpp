#include <bits/stdc++.h>

using namespace std;
#define int long long

struct segment_tree {
	vector <int> tree;
	vector <int> arr;
	int n;
	segment_tree() {
		tree = {};
		arr = {};
		n = 0;
	}


	segment_tree(vector <int> a) {
		n = a.size();
		arr = a;
		tree.resize(n * 4)
	}
	void build(int v, int l, int r) {
		if (l == r - 1) {
			tree[v] = l;
			return;
		}
		int m =  (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		if (arr[tree[v * 2]] >= arr[tree[v * 2 + 1]]) {
			tree[v] = tree[v * 2];
		}
		else {
			tree[v] = tree[v * 2 + 1];
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 1e9;
		if (tl == tr - 1)
			return arr[tree[v]];
		int tm = (tl + tr) / 2;
		if (arr[tree[v * 2]] >= r)
			return get(v * 2, tl, tm, l, r);
		else
			return get(v * 2 + 1, tm, tr, l, r);
	}

	int get(int l, int r) {
		return r - get(1, 0, n, l, r);
	}

	void build() {
		build(1, 0, n);
	}
};

struct help_segment_tree {
	vector <int> tree;
	vector <int> arr;
	int n;
	help_segment_tree() {
		tree = {}
		arr = {}
		n = 0;
	}


	help_segment_tree(vector <int> a) {
		n = a.size();
		arr = a;
		tree.resize(n * 4);
	}


	void build(int v, int l, int r) {
		if (l == r - 1) {
			tree[v] = arr[l];
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	void build() {
		build(1, 0, n);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return -1e9;
		if (tl >= l && tr <= r) {
			return tree[v];
		}
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r);
	}
};

struct two_coord_segment_tree {
	vector <pair <vector <pair <int, int> >, help_segment_tree> > tree;
	vector <pair <int, int> > arr;
	int n;
	two_coord_segment_tree() {
		tree = {};
		arr = {};
		n = 0;
	}

	two_coord_segment_tree(vector <int> a) {
		n = a.size();
		arr.resize(n);
		for (int i = 0; i < n; i++){
			arr[i].first = i + a[i];
			arr[i].second = a[i];
		}
		tree.resize(n * 4);
	} 

	void build(int v, int l, int r) {
		if (l == r - 1) {
			vector <pair <int, int> > help;
			help.push_back(arr[l]);
			tree[v].first = help;
			tree[v].second = help_segment_tree({tree[v].first[0].second});
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		int pos1 = 0, pos2 = 0;
		while (pos1 < tree[v * 2].first.size() && pos2 < tree[v * 2 + 1].first.size()) {
			if (tree[v * 2].first[pos1] < tree[v * 2 + 1].first[pos2]) {
				tree[v].first.push_back(tree[v * 2].first[pos1++]);
			}
			else {
				tree[v].first.push_back(tree[v * 2 + 1].first[pos2++]);
			}
		}

		while (pos1 < tree[v * 2].first.size()) {
			tree[v].first.push_back(tree[v * 2].first[pos1++]);
		}

		while (pos2 < tree[v * 2 + 1].first.size()) {
			tree[v].first.push_back(tree[v * 2 + 1].first[pos2++]);
		}
		vector <int> a;
		for (auto i : tree[v].first)
			a.push_back(i.second);
		tree[v].second = help_segment_tree(a);
	}

	void build() {
		build(1, 0, n);
	}


	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r) {
			int pos = upper_bound(tree[v].first.begin(), tree[v].first.end(), {r, 0}) - tree[v].first.begin();
			return tree[v].second.get(0, pos);
		}
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r);
	}
};


int n;
const int MAXN = 1e5 + 10;
const int INF = 1e9;
int arr[MAXN];
int dp[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

int get_ans(int l, int r) {

}


void run() {
	map <int, int> used;
	for (int i = 0; i < n; i++)
		used[arr[i]] = INF;
	for (int i = n - 1; i >= 0; i--) {
		dp[i] = min(dp[i + 1] + 1, used[arr[i]] - i - 1);
	}
	for (int i = 0; i < n; i++) {
		dp[i] += i;
	}
	int m;
	cin >> m;
	for (int test = 0; test < m; test++) {
		int l, r;
		cin >> l >> r;
		int ax = get_ans(l, r);
		ans.push_back(ax);
	}
}

void write() {
	for (auto i : ans)
		cout << i << '\n';
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