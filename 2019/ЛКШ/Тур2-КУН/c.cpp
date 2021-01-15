#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 4e3 + 10;
vector<int> g[MAXN], gr[MAXN];
int mt1[MAXN];
int n, m;

void read() {
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; j++) {
			int v;
			cin >> v;
			v--;
			g[i].push_back(v);
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> mt1[i];
		mt1[i]--;
		if (mt1[i] != -1)
			gr[mt1[i]].push_back(i);
	}
}

bool used1[MAXN], used2[MAXN];

void dfs2(int v);

void dfs1(int v) {
	used1[v] = true;
	for (auto i : g[v]) {
		if (!used2[i] && mt1[v] != i)
			dfs2(i);
	}
}

void dfs2(int v) {
	used2[v] = true;
	for (auto i : gr[v]) {
		if (!used1[i])
			dfs1(i);
	}
}

vector<int> ans1, ans2;

void run() {
	for (int i = 0; i < m; i++) {
		if (!used1[i] && mt1[i] == -1) {
			dfs1(i);
		}
	}

	for (int i = 0; i < m; i++) {
		if (!used1[i])
			ans1.push_back(i + 1);
	}
	for (int i = 0; i < n; i++) {
		if (used2[i]) 
			ans2.push_back(i + 1);
	}
}

void write() {
	cout << ans1.size() + ans2.size() << endl;
	cout << ans1.size() << " ";
	for (auto i : ans1) 
		cout << i << " ";
	cout << endl;
	cout << ans2.size() << " ";
	for (auto i : ans2) 
		cout << i << " ";
	cout << endl;
}

signed main() {
	freopen("minimal.in", "r", stdin);
	freopen("minimal.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
3 2
2 1 2
1 2
1 2
1 2 0

*/