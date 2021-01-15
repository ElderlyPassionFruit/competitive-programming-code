#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 2e5 + 1;
int n, k;
vector<int> adj[MAXN];
int le[MAXN];
int ss[MAXN];
int vis[MAXN];

void dfs(int no, int par = -1, int lev = 0) {
	le[no] = lev;
	ss[no] = 1;
	for (auto nn : adj[no]) {
		if (nn != par) {
			dfs(nn, no, lev + 1);
			ss[no] += ss[nn];
		}
	}
} 

int tot = 0;

void dfs2(int no, int par = -1, int lev = 0) {
	if (vis[no] == 1) {
		tot += lev;
	}
	for (auto nn : adj[no]) {
		if (nn != par) {
			if (vis[no] == 1) {
				dfs2(nn, no, lev);
			} else {
				dfs2(nn, no, lev + 1);
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(0);
	vector<pair<pair<int, int>, int>> kk;
	for (int i = 0; i < n; i++) {
		kk.push_back({{-(le[i] - (ss[i] - 1)), 0}, i});
	}
	sort(all(kk));
	
	cout << "kk = " << endl;
	for (auto i : kk) {
		cout << i.first.first << " " << i.second << endl;
	}
	for (int i = 0; i < n; i++) {
		vis[i] = 0;
	}
	for (int i = 0; i < k; i++) {
		vis[kk[i].second] = 1;
	}
	dfs2(0);
	cout << tot << endl;
	return 0;
}