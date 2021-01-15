#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
const int MOD = 1e9 + 7;
const int MAXN = 1e3 + 10;

int n;
int z[MAXN];
vector<int> g[MAXN];
vector<int> gr[MAXN];
int color[MAXN];
int used[MAXN];

void dfs(int v, int c) {
	color[v] = c;
	for (auto i : g[v]) {
		if (color[i] == -1)
			dfs(i, c);
	}
}
 
int get(int cnt) {
	int ans = 1;
	for (int i = 0; i < cnt; i++)
		ans = ans * 2LL % MOD;
	return ans;
}

void no() {
	cout << 0 << endl;
	exit(0);
}

void dfs_color(int v, int c) {
	used[v] = c;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs_color(i, 3 - c);
		}
		else {
			if (used[i] == used[v]) no();
		}
	} 
}

int c;

void build() {
	if (z[0] > 0) no();
	for (int i = 1; i < n; i++) {
		if (z[i] == -1) continue;
		if (i + z[i] > n) no();
		for (int j = 0; j < z[i]; j++) {
			g[j].push_back(i + j);
			g[i + j].push_back(j);
		}
	}
	for (int i = 0; i < n; i++) {
		color[i] = -1;
	}
	c = 0;
	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			dfs(i, c++);
		}
	}
	for (int i = 1; i < n; i++) {
		if (z[i] == -1) continue;
		if (i + z[i] < n && color[i + z[i]] == color[z[i]]) {
			no();
		}
	}

	for (int i = 1; i < n; i++) {
		if (z[i] == -1) continue;
		if (i + z[i] < n) {
			g[i + z[i]].push_back(z[i]);
			g[z[i]].push_back(i + z[i]);
			gr[i + z[i]].push_back(z[i]);
			gr[z[i]].push_back(i + z[i]);
		}
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_color(i, 1);
		}
	}

	for (int i = 0; i < n; i++) {
		color[i] = -1;
	}
	c = 0;
	for (int i = 0; i < n; i++) {
		if (color[i] == -1) {
			dfs(i, c++);
		}
	}
	//cout << "c = " << c << endl;
}

int get_ans() {
	return get(c);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> z[i];
	build();
	cout << get_ans() << endl;
	return 0;
}








