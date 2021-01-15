#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e3 + 10;
vector<int> g[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;
		g[i].resize(m);
		for (int j = 0; j < m; j++) {
			int v;
			cin >> v;
			v--;
			g[i][j] = v;
		}
	}
}

int color[MAXN];

bool dfs(int v) {
	color[v] = 1;
	bool flag = true;
	for (auto i : g[v]) {
		if (color[i] == 1)
			return false;
		if(color[i] == 0)
		flag &= dfs(i);	
	}
	color[v] = 2;
	return flag;
}

bool check() {
	bool flag = true;
	for (int i = 0; i < n; i++) {
		if (!color[i]) {
			flag &= dfs(i);
		}
	}
	return flag;
}

bool used[MAXN];

vector<int> ans;

void dfs_ans(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_ans(i);
		}
	}
	ans.push_back(v);
}

void run() {
	if (!check()) {
		cout << "-1" << endl;
		exit(0);
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs_ans(i);
		}
	}
	reverse(ans.begin(), ans.end());
}

void write() {
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << endl;
}

signed main() {
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}