#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;

int n, m;
int lett[MAXN];
vector<char> fans = {'R', 'G', 'B'};
vector<int> g[MAXN], gr[MAXN];

void link(int u, int v) {
	g[u].pb(v);
	gr[v].pb(u);
}

void add(int u, int v) {
	if (lett[v] == lett[u]) {
		link(v * 2, u * 2 + 1);
		link(v * 2 + 1, u * 2);
	}
	else if ((lett[v] + 1) % 3 == lett[u]) {
		link(v * 2 + 1, u * 2 + 1);
	}
	else {
		link(v * 2, u * 2);
	}
}

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		char x;
		cin >> x;
		if (x == 'R')
			lett[i] = 0;
		else if (x == 'G')
			lett[i] = 1;
		else 
			lett[i] = 2;	
	}

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		add(u, v);
		add(v, u);
	}
}

bool used[MAXN];
int color[MAXN];
vector<int> order;

void dfs_order(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_order(i);
		}
	}
	order.pb(v);
}

void dfs_color(int v, int c) {
	used[v] = true;
	color[v] = c;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs_color(i, c);
		}
	}
}

int jump[MAXN];

void run() {
	for (int i = 0; i < 2 * n; i++) {
		if (!used[i]) {
			dfs_order(i);
		}
	}

	for (int i = 0; i < 2 * n; i++) {
		used[i] = false;
	}

	int c = 0;
	reverse(order.begin(), order.end());
	for (auto i : order) {
		if (!used[i]) {
			dfs_color(i, c++);
		}
	}

	for (int i = 0; i < n; i++) {
		if (color[i * 2] == color[i * 2 + 1]) {
			cout << "Impossible" << endl;
			exit(0);
		}
	}

	for (int i = 0; i < n; i++) {
		if (color[i * 2] > color[i * 2 + 1]) {
			jump[i] = 1;
		}
		else {
			jump[i] = 2;
		}
	}
}

void write() {
	for (int i = 0; i < n; i++) {
		cout << fans[(lett[i] + jump[i]) % 3];
	}
	cout << endl;
}

signed main() {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}