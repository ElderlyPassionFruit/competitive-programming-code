#include <bits/stdc++.h>

using namespace std;
#define int long long
const int MAXN = 1e5 + 10;
set <int> g[MAXN], gr[MAXN];
set <pair <int, int> > ed;
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ed.insert({u, v});
		g[u].insert(v);
		gr[v].insert(u);
	}
}

bool used[MAXN];
int comps[MAXN];
vector <int> order;
int comp = 0;

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i])
			dfs(i);
	}
	order.push_back(v);
}

void dfs2(int v) {
	comps[v] = comp;
	used[v] = true;
	for (auto i : gr[v]) {
		if (!used[i]) {
			dfs2(i);	
		}
	}
}

int ans;
void run() {
	for (int i = 0; i < MAXN; i++) {
		used[i] = false;
		comps[i] = -1;
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i);
		}
	}
	for (int i = 0; i < MAXN; i++)
		used[i] = false;

	reverse(order.begin(), order.end());
	
	for (auto i : order) {
		if (!used[i]){
			dfs2(i);
			comp++;
		}
	}
	

	map <int, int> help;
	for (int i = 0; i < n; i++) {
		if (help.count(comps[i]))
			help[comps[i]]++;
		else
			help[comps[i]] = 1;
	}

	ans = 0;
	for (auto i : help) {
		ans = ans + i.second * (i.second - 1);
	}

	for (auto i : ed) {
		if (comps[i.first] == comps[i.second]) {
			ans = ans - 1;
		}
	}
}

void write() {
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