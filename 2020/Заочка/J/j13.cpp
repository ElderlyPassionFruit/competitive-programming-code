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
int n;
int cnt;

int query(vector<int> a) {
	cnt++;
	assert(cnt <= 10);
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

vector<int> order;

void dfs_order(int v, int p) {
	for (auto i : g[v]) {
		if (i != p) {
			dfs_order(i, v);
		}
	}
	order.push_back(v);
}

vector<int> get_seg(int l, int r, vector<int> a) {
	vector<int> ans;
	for (int i = l; i <= r; i++)
		ans.push_back(a[i]);
	return ans;
}

int get_first() {
	dfs_order(0, 0);
	reverse(all(order));
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

vector<int> fq(int l, int r, vector<int> a, int last) {
	vector<int> ans;
	for (int i = l; i <= r; i++)
		ans.push_back(a[i]);
	for (int i = last; i < a.size(); i++)
		ans.push_back(i);
	return ans;
}

int get_next(int & last) {
	int l = -1, r = last;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int fans = query(fq(0, mid, order, last + 1));
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
	int ans = get_first();
	out_ans({ans});
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