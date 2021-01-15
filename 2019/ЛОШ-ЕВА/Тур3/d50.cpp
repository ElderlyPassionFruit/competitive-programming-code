#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
vector<int> g[MAXN];
vector<int> gr[MAXN];
set<pair<int, int> > ed;
int n, m;

int query(int u, int v) {
	cout << "? " << u + 1 << " " << v + 1 << endl;
	int ans;
	if (ans == -1) {
		while (true) {
			ans = -1;
		}
	}
	cin >> ans;
	return ans;
}


void out_ans(int v) {
	cout << "! " << v + 1 << endl;
	exit(0);
}

void solve1() {
	int root = 0;
	for (int i = 1; i < n; i++) {
		int q = query(root, i);
		if (q == 0) root = i;
	}
	out_ans(root);
}

void read() {
	cin >> n >> m;
	if (m == 0) {
		solve1();
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ed.insert({u, v});
		ed.insert({v, u});
		gr[u].push_back(v);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ed.count({i, j})) continue;
			int q = query(i, j);
			if (q == 1)
				g[i].push_back(j);
			else
				g[j].push_back(i);
		}
	}
}

bool used[MAXN], used2[MAXN];

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v])
		if (!used[i])
			dfs(i);
}

void dfs2(int v) {
	used2[v] = true;
	for (auto i : gr[v])
		if (!used2[i])
			dfs2(i);
}

void clear() {
	for (int i = 0; i < n; i++){
		used[i] = false;
		used2[i] = false;
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		dfs(i);
		dfs2(i);
		int cnt = 0;
		for (int j = 0; j < n; j++)
			cnt += used[j] | used2[j];
		if (cnt == n) out_ans(i);
		clear();
	}
}



void write() {

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