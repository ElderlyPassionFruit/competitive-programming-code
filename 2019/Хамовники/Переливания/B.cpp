#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 3*1e5 + 10;
vector <int> g[MAXN];
int n;
int q;
map <int, set <int> > need;
vector <pair <int, int> > fans;
void read() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		p--;
		g[i].push_back(p);
		g[p].push_back(i);
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		int v, h;
		cin >> v >> h;
		v--;
		need[v].insert(h);
		fans.push_back({v, h});
	}
}

void mer(unordered_map <int, int> &a, unordered_map <int, int> &b) {
	for (auto i : b)
		a[i.first] += i.second;
}

int sz[MAXN], h[MAXN];

void dfs_help(int v, int p, int len) {
	sz[v] = 1;
	h[v] = len;
	for (auto i : g[v]) { 
		if (i != p) {
			dfs_help(i, v, len + 1);
			sz[v] += sz[i];
		}
	}
}

map <pair <int, int>, int > ans;

unordered_map <int, int> dfs(int v, int p) {
	unordered_map <int, int> res;
	int size = 0;
	int pos = -1;
	for (auto i : g[v]) {
		if (i != p && sz[i] > size) {
			size = sz[i];
			pos = i;
		}
	}

	if (pos != -1) {
		res = dfs(pos, v);
	}
	
	res[h[v]]++;

	for (auto i : g[v]) {
		if (i != p && i != pos) {
			unordered_map <int, int> s = dfs(i, v);
			mer(res, s);
		}
	}

	for (auto i : need[v]) {
		ans[{v, i}] = res[h[v] + i];
	}
	return res;
}

void run() {
	dfs_help(0, 0, 0);
	dfs(0, 0);
}

void write() {
	for (auto i : fans){
		cout << ans[i] << '\n';
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