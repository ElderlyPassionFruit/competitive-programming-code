#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 1e5 + 10;
map <string, int> help;

vector<pair <string, string> > ed;

int n;
vector<int> g[MAXN];
int p[MAXN];

void read() {
	cin >> n;
	set<string> z;
	for (int i = 0; i < n - 1; i++) {
		string a, b;
		cin >> a >> b;
		z.insert(a);
		z.insert(b);
		ed.push_back({a, b});
	}
	int cnt = 0;
	for (auto i : z)
		help[i] = cnt++;
}

int h[MAXN];

void dfs(int v, int p, int len) {
	h[v] = len++;
	for (auto i : g[v]) {
		if (i != p)
			dfs(i, v, len);
	}
}

vector<pair<string, int> > ans;

void run() {
	set <int> root;
	for (int i = 0; i < n; i++)
		root.insert(i);
	for (auto i : ed) {
		int v = help[i.first];
		int u = help[i.second];
		g[u].push_back(v);
		g[v].push_back(u);
		root.erase(v);
	}
	int t = *root.begin();
	dfs(t, -1, 0);
	for (auto i : help)
		ans.push_back({i.first, h[i.second]});
}

void write() {
	sort(ans.begin(), ans.end());
	for (auto i : ans)
		cout << i.first << " " << i.second << "\n"; 
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