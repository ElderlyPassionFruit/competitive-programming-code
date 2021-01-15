#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, m;
vector<int> g[MAXN];
vector<int> a;
vector<pair <int, int> > ed;
void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		ed.push_back({u, v});
	}
}

vector<int> get(int x) {
	vector<int> ans;
	for (int i = 2; i * i <= x; i++) {
		while (x % i == 0) {
			ans.push_back(i);
			x /= i;
		}
	}
	if (x > 1)
		ans.push_back(x);
	return ans;
}

int cnt = 0;

void build() {
	vector<vector<pair <int, int> > > vert(n);
	for (int i = 0; i < n; i++) {
		auto help = get(a[i]);
		for (auto j : help) {
			vert[i].push_back({cnt++, j});
		}
	}

	for (auto e : ed) {
		int i = e.first;
		int j = e.second;
		for (auto x : vert[i]) {
			for (auto y : vert[j]) {
				if (x.second == y.second) {
					if (i % 2 == 0)
						g[x.first].push_back(y.first);
					else
						g[y.first].push_back(x.first);
				}
			}
		}
	}
}

int mt[MAXN], used[MAXN];

bool dfs(int v, int col) {
	if (used[v] == col)
		return false;
	used[v] = col;
	for (auto i : g[v]) {
		if (mt[i] == -1 || dfs(mt[i], col)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

int ans;

void run() {
	build();
	for (int i = 0; i < cnt; i++) {
		mt[i] = -1;
		used[i] = -1;
	}
	int col = 0;
	for (int i = 0; i < cnt; i++) {
		dfs(i, col++);
	}
	ans = 0;
	for (int i = 0; i < cnt; i++) {
		if (mt[i] != -1)
			ans++;
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