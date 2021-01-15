#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 10;
int n, m, k;
int c[MAXN];
vector<int> g[MAXN];
int deg[MAXN]; 

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++){
		cin >> c[i];
		if (c[i] != -1) c[i]--;
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		if (c[v] == -1 && c[u] == -1) {
			deg[v]++;
			deg[u]++;
		}
	}
	for (int i = 0; i < n; i++) {
		sort(all(g[i]), [&](int a, int b) {return c[a] < c[b];});
	}
}

void no() {
	cout << "No\n";
	exit(0);
}

bool used[MAXN];
vector<int> path;
bool cycle;

void dfs_path(int v, int p) {
	used[v] = true;
	path.push_back(v);
	int cnt = 0;
	for (auto i : g[v]) {
		if (i == p) continue;
		if (c[i] != -1) continue;
		if (used[i]) {
			cycle = true;
			continue;
		}
		dfs_path(i, v);
		cnt++;
	}
	assert(cnt <= 2);
}

int have[MAXN][3];

void gen(int pos, int v) {
	for (int i = 0; i < 3; i++) have[pos][i] = -1;
	int last = -1;
	int cnt = 0;
	for (auto i : g[v]) {
		if (c[i] > last + 1) {
			for (int j = last + 1; j < c[i] && cnt < 3; j++, cnt++) {
				have[pos][cnt] = j;
			}
		}
		last = c[i];
	}
	for (int j = last + 1; j < k && cnt < 3; j++, cnt++) {
		have[pos][cnt] = j;
	} 
}

void make_colors() {
	for (int i = 0; i < (int)path.size(); i++) {
		gen(i, path[i]);
	}
}

int par[MAXN][3];

void calc_dp(int start_color) {
	for (int i = 0; i < 3; i++) {
		par[0][i] = -1;
		if (have[0][i] == start_color) {
			par[0][i] = i;
		}
	}
	for (int i = 1; i < (int)path.size(); i++) {
		for (int my_color = 0; my_color < 3; my_color++) {
			par[i][my_color] = -1;
			if (have[i][my_color] == -1) continue;
			for (int last_color = 0; last_color < 3; last_color++) {
				if (have[i - 1][last_color] == -1) continue;
				if (par[i - 1][last_color] == -1) continue;
				if (have[i - 1][last_color] == have[i][my_color]) continue;
				par[i][my_color] = last_color;
				break;
			}
		}
	}
}

int check(int start_color) {
	if (!cycle) {
		for (int i = 0; i < 3; i++) {
			if (par[(int)path.size() - 1][i] != -1) {
				return i;
			}
		}
		return -1;
	} else {
		for (int i = 0; i < 3; i++) {
			if (par[(int)path.size() - 1][i] == -1) continue;
			if (have[(int)path.size() - 1][i] == start_color) continue;
			return i;
		}
		return -1;
	}
}

int ans[MAXN];

void make_ans(int last_color) {
	for (int i = (int)path.size() - 1; i >= 0; i--) {
		ans[path[i]] = have[i][last_color];
		last_color = par[i][last_color];
	}
}

void paint(int v) {
	path.clear();
	cycle = false;
	dfs_path(v, -1);

	make_colors();

	for (int i = 0; i < 3 && have[0][i] != -1; i++) {
		calc_dp(have[0][i]);
		int last_color = check(have[0][i]);
		if (last_color != -1) {
			make_ans(last_color);
			return;
		}
	}
	no();
}

void run() {
	for (int i = 0; i < n; i++) {
		if (c[i] == -1 && !used[i] && deg[i] == 1) {
			paint(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (c[i] == -1 && !used[i]) {
			paint(i);
		}
	}
	for (int i = 0; i < n; i++) {
		if (c[i] != -1) {
			ans[i] = c[i];
		}
	}
}

void write() {
	cout << "Yes\n";
	for (int i = 0; i < n; i++) {
		cout << ans[i] + 1 << " ";
	}
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