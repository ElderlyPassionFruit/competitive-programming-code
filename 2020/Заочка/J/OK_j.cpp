#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
vector<int> g[MAXN];
vector<int> order;
int p[MAXN];
int n;
int cnt;

int query(vector<int> a) {
	cnt++;
	assert(cnt <= 100);
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	cout << "? " << a.size() << " ";
	for (auto i : a)
		cout << i + 1 << " ";
	cout << endl;
	int ans;
	cin >> ans;
	assert(ans != -1);
	return ans;
}

void out_ans(vector<int> a) {
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	cout << "! " << a.size() << " ";
	for (auto i : a)
		cout << i + 1 << " ";
	cout << endl;
}

void dfs_order(int v, int par) {
	p[v] = par;
	order.push_back(v);
	for (auto i : g[v]) {
		if (i != par) {
			dfs_order(i, v);
		}
	}
}

vector<int> get_seg(int l, int r, vector<int> a) {
	vector<int> ans;
	for (int i = l; i <= r; i++)
		ans.push_back(a[i]);
	return ans;
}

int get_first() {
	order.clear();
	dfs_order(0, 0);
	int l = -1, r = n - 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int fans = query(get_seg(0, mid, order));
		if (fans)
			r = mid;
		else
			l = mid;
	}
	return order[r];
}

vector<int> merge(vector<int> a, vector<int> b) {
	for (auto i : b)
		a.push_back(i);
	return a;
}

int get_next(int & last, vector<int> must) {
	int l = -1, r = last;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int fans = query(merge(get_seg(0, mid, order), must));
		if (fans)
			r = mid;
		else
			l = mid;
	}
	last = r - 1;
	return order[r];
}

void solve() {
	cnt = 0;
	int root = get_first();
	order.clear();
	dfs_order(root, root);
	vector<int> ans;
	ans.push_back(root);

	int last = n - 1;
	vector<int> must;

	while (last > 0 && ans.size() < 10) {
		int x = get_next(last, must);
		ans.push_back(x);
		while (x != root) {
			must.push_back(x);
			x = p[x];
		}
		sort(all(ans));
		ans.resize(unique(all(ans)) - ans.begin());
	}
	out_ans(ans);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	char x;
	while (true) {
		cin >> x;
		if (x == 'E')
			return 0;
		solve();
	}
	return 0;
}