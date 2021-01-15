#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
const int MAXN = 2e5 + 10;
vector <int> g[MAXN];
vector <pair <int, int> > ed;
void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		g[v].push_back(u);
		g[u].push_back(v);
		ed.push_back({u, v});
	}
}

int color[MAXN];

void dfs(int v, int p, int c) {
	color[v] = c;
	for (auto i : g[v]) {
		if (i != p) {
			if (color[i] == 0) {
				dfs(i, v, 3 - c);
			}
			else if (color[i] == c) {
				cout << "NO" << endl;
				exit(0);
			}
		}
	}
}

string ans = "";
void run() {
	dfs(0, 0, 1);
	for (auto i : ed) {
		if (color[i.first] == 1) {
			ans += "1";
		}
		else {
			ans += "0";
		}
	}
}

void write() {
	cout << "YES" << endl;
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