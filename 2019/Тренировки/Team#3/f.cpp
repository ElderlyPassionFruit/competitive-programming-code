#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<vector<int>> g, gr;

void read() {
	cin >> n;
	g.resize(n);
	gr.resize(n);
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz;
		g[i].resize(sz);
		for (int j = 0; j < sz; j++) {
			cin >> g[i][j];
			g[i][j]--;
		}
		sort(g[i].begin(), g[i].end());
	}
}

void merge(vector<int> & a, vector<int> b) {
	for (auto i : b)
		a.push_back(i);
}

vector<int> dfs(int v, int p) {
	vector<int> ans;
	for (auto i : gr[v]) {
		if (i != p) {
			auto x = dfs(i, v);
			merge(ans, x);
		}
	}
	sort(ans.begin(), ans.end());
	if (ans != g[v]) {
		cout << "NO" << endl;
		exit(0);
	}
	ans.push_back(v);
	return ans;
}

vector<int> pred;

void run() {
	pred.assign(n, -1);
	vector<int> a;
	for (int i = 0; i < n; i++) {
		a.push_back(i);
	}
	sort(a.begin(), a.end(), [&] (int i, int j) {return g[i].size() > g[j].size();});
	for (auto i : a) {
		for (auto j : g[i]) {
			pred[j] = i;
		}
	}
	/*cout << "pred = " << endl;
	for (auto i : pred) {
		cout << i << endl;
	}*/
	int root = -1;
	for (int i = 0; i < n; i++) {
		if (pred[i] == -1) {
			if (root != -1) {
				cout << "NO" << endl;
				exit(0);
			}
			root = i;
		}
		else {
			gr[i].push_back(pred[i]);
			gr[pred[i]].push_back(i);
		}
	}
	if (root == -1) {
		cout << "NO" << endl;
		exit(0);
	}
	dfs(root, -1);
}

void write() {
	cout << "YES" << endl;
	for (int i = 0; i < n; i++) {
		if (pred[i] != -1) {
			cout << pred[i] + 1 << " " << i + 1 << endl;
 		}
	}
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