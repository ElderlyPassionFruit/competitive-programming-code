#include <bits/stdc++.h>

using namespace std;
#define int long long

const int INF = 1e18, min_l = -1e5 - 10, max_r = 1e5 + 10;;
const int MAXN = 1e5 + 10;
int n;
int a[MAXN], b[MAXN], sz[MAXN], dp[MAXN];
vector <int> g[MAXN];

struct line{
	int k, b;
	line() {
		k = 0, b = INF;
	}
	line(int x, int y) {
		k = x, b = y;
	}
};

int eval(line l, int x) {
	return l.k * x + l.b;
}		

struct li_tree{
	unordered_map <int, line> tree;
	vector <line> help;

	li_tree(){
		tree = {};
		help = {};
	}

	void upd(line l, int v = 1, int tl = min_l, int tr = max_r) {
		int tm = (tl + tr) / 2;
		bool mid = eval(l, tm) < eval(tree[v], tm);
		bool left = eval(l, tl) < eval(tree[v], tl);
		if (mid) {
			swap(l, tree[v]);
		}
		if (tl == tr - 1)	return;
		if (mid != left) {
			upd(l, v * 2, tl, tm);
		}
		else {
			upd(l, v * 2 + 1, tm, tr);
		}
	}

	void add(line l) {
		upd(l);
		help.push_back(l);
	}

	int get(int pos, int v = 1, int tl = min_l, int tr = max_r) {
		if (tl >= pos + 1 || tr <= pos) return INF;
		if (tl == pos && tr == pos + 1) return eval(tree[v], pos);
		int tm = (tl + tr) / 2;
		int ans = eval(tree[v], pos);
		ans = min(ans, get(pos, v * 2, tl, tm));
		ans = min(ans, get(pos, v * 2 + 1, tm, tr));
		return ans;
	}
};

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
}

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

bool cmp(int a, int b) {
	return sz[a] > sz[b];
}

void merge(li_tree &a, li_tree b) {
	for (auto i : b.help) {
		a.add(i);
	}
}

li_tree dfs(int v, int p) {
	if (sz[v] == 1) {
		li_tree ans;
		ans.add(line(b[v], dp[v]));
		return ans;
	}

	li_tree ans;
	bool flag = false;
	for (auto i : g[v]) {
		if (i != p) {
			if (!flag) {
				ans = dfs(i, v), flag = true;
			}
			else {
				merge(ans, dfs(i, v));
			}
		}
	}

	dp[v] = ans.get(a[v]);	
	ans.add(line(b[v], dp[v]));

	return ans;
}

void run() {
	dfs_sz(0, -1);
	for (int i = 0; i < n; i++) {
		sort(g[i].begin(), g[i].end(), cmp);
	}
	dfs(0, 0);
}

void write() {
	for (int i = 0; i < n; i++)
		cout << dp[i] << " ";
	cout << endl;
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