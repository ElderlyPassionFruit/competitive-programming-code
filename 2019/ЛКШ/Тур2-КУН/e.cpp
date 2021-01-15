#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 110;
int table[MAXN][MAXN];
vector<int> g[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> table[i][j];
		}
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				chkmax(table[i][j], min(table[i][k], table[k][j]));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (table[i][j]) {
				g[i].pb(j);
			}
		}
	}
}

int mt[MAXN], used[MAXN];

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v]) {
		if (mt[i] == -1 || dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

int used1[MAXN], used2[MAXN];
vector<int> g1[MAXN], g2[MAXN];

void dfs2(int v);

void dfs1(int v) {
	used1[v] = true;
	for (auto i : g1[v]) {
		if (!used2[i] && mt[i] != v) {
			dfs2(i);
		}
	}
}

void dfs2(int v) {
	used2[v] = true;
	for (auto i : g2[v]) {
		if (!used1[i]) {
			dfs1(i);
		}
	}
}

bool vert[MAXN];
bool bad[MAXN];

vector<int> ans;

void run() {
	for (int i = 0; i < MAXN; i++) {
		used[i] = -1;
		mt[i] = -1;
	}
	for (int i = 0; i < n; i++) {
		dfs(i, i);
	}

	for (int i = 0; i < n; i++) {
		g1[i] = g[i];
	}

	for (int i = 0; i < n; i++) {
		if (mt[i] != -1) {
			g2[i].push_back(mt[i]);
		}
	}

	for (int i = 0; i < n; i++) {
		if (mt[i] != -1)
			vert[mt[i]] = true;
	}

	for (int i = 0; i < n; i++) {
		if (!used1[i] && !vert[i])
			dfs1(i); 
	}

	for (int i = 0; i < n; i++) {
		if (!used1[i] || used2[i]) continue;
		ans.push_back(i + 1);
	}
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}

signed main() {
	freopen("hobbits.in", "r", stdin);
	freopen("hobbits.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
2
0 1
0 0

3
0 0 0
0 0 0
0 0 0


*/