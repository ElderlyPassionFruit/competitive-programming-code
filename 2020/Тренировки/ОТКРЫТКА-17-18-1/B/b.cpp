#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
vector<int> g[MAXN], gr[MAXN];
int n, m, h;
int a[MAXN];

bool check(int a, int b) {
	return (b - a == 1) || (a == h - 1 && b == 0);
}

void read() {
	cin >> n >> m >> h;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		if (check(a[u], a[v])) {
			g[u].push_back(v);
			gr[v].push_back(u);
		}
		if (check(a[v], a[u])) {
			g[v].push_back(u);
			gr[u].push_back(v);
		}
	}
}

vector<bool> used;
vector<int> order;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_order(i);
		}
	}
	order.push_back(v);
}

vector<int> color;
vector<int> cnt;

void dfs_color(int v, int c) {
	color[v] = c;
	cnt[c]++;
	for (auto i : gr[v]) {
		if (color[i] == -1) {
			dfs_color(i, c);
		}
	}
}

vector<int> ans;

void run() {
	/*cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << endl;
		for (auto j : g[i]) {
			cout << j << " ";
		}
		cout << endl;
	}*/


	used.assign(n, 0);
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_order(i);
		}
	}
	reverse(all(order));
	/*cout << "order = " << endl;
	for (auto i : order)
		cout << i << " ";
	cout << endl;*/
	int c = 0;
	color.assign(n, -1);

	for (auto i : order) {
		if (color[i] == -1) {
			cnt.push_back(0);
			dfs_color(i, c++);
		}
	}

	/*cout << "color = " << endl;
	for (auto i : color) {
		cout << i << " ";
	}
	cout << endl;*/

	vector<bool> good(c, 1);
	for (int i = 0; i < n; i++) {
		for (auto j : g[i]) {
			int u = color[i], v = color[j];
			if (u == v) continue;
			good[u] = false;
		}
	}

	int fans = n;
	c = 0;
	for (int i = 0; i < cnt.size(); i++) {
		if (fans > cnt[i] && good[i]) {
			fans = cnt[i];
			c = i;
		}
	}
	for (int i = 0; i < n; i++) {
		if (color[i] == c) {
			ans.push_back(i);
		}
	}
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << "\n";
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