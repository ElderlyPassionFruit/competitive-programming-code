#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n;
vector<int> g[MAXN];
int l[MAXN], r[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
	} 
}

bool ans[MAXN];

struct event{
	int l, r;
	bool flag;
	event() {}
	event(int a, int b, bool c) {
		l = a, r = b, flag = c;
	}
};

event merge(event a, event b) {
	a.flag &= b.flag;
	chkmax(a.l, b.l);
	chkmin(a.r, b.r);
	a.flag &= (a.l <= a.r);
	return a;
}

vector<event> pref[MAXN];
vector<event> suff[MAXN];

const int INF = 1e10;

int sz[MAXN];

void dfs_sz(int v, int p) {
	sz[v] = 1;
	for (auto i : g[v]) {
		if (i != p) {
			dfs_sz(i, v);
			sz[v] += sz[i];
		}
	}
}

void build(int v) {
	suff[v] = pref[v];
	for (int i = 1; i < (int)pref[v].size(); i++) {
		pref[v][i] = merge(pref[v][i], pref[v][i - 1]);
	}
	for (int i = (int)suff[v].size() - 2; i >= 0; i--) {
		suff[v][i] = merge(suff[v][i], suff[v][i + 1]);
	}
}

event dfs_down(int v) {
	event fans(-INF, INF, true);
	for (int i = 0; i < g[v].size(); i++) {
		int u = g[v][i];
		auto x = dfs_down(u);
		pref[v].push_back(x);
		fans = merge(fans, x);	
	}
	build(v);

	if (fans.l == -INF && fans.r == INF) {
		fans.l = 0;
		fans.r = 0;
	}

	fans.flag &= (fans.l <= fans.r);
	fans.l += l[v];
	fans.r += r[v];
	return fans;
}

void solve(int v, event p) {
	if (!pref[v].empty()) {
		p = merge(p, pref[v].back());
	}
	ans[v] = p.flag;
}

event get(int v, int pos, event p) {
	event fans(-INF, INF, true);
	if (pos + 1 < (int)suff[v].size()) {
		fans = merge(fans, suff[v][pos + 1]);
	}
	if (pos - 1 >= 0) {
		fans = merge(fans, pref[v][pos - 1]);
	}
	fans = merge(fans, p);
	fans.l += l[v];
	fans.r += r[v];
	return fans;
}

void dfs_up(int v, event p) {
	solve(v, p);
	for (int i = 0; i < g[v].size(); i++) {
		int u = g[v][i];
		//cout << "v = " << v << " u = " << u << endl;
		//cout << "p = " << p.l << " " << p.r << " " << p.flag << endl;
		//cout << "get = " << get(v, i, p).l << " " << get(v, i, p).r << " " << get(v, i, p).flag << endl;
		//cout << endl;
		dfs_up(u, get(v, i, p));
	}
}

void build() {
	dfs_sz(0, 0);
	for (int i = 1; i < n; i++) {
		sort(g[i].begin(), g[i].end(), [&] (int i, int j) {return sz[i] < sz[j];});
		g[i].pop_back();
	}
}

void run() {
	build();
	/*cout << "l = " << endl;
	for (int i = 0; i < n; i++)
		cout << l[i] << " ";
	cout << endl;
	cout << "r = " << endl;
	for (int i = 0; i < n; i++)
		cout << r[i] << " ";
	cout << endl;
	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : g[i])
			cout << j << " ";
		cout << endl;
	}*/
	dfs_down(0);
	/*cout << "pref = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : pref[i])
			cout << j.l << " " << j.r << " " << j.flag << endl; 
		cout << endl;
	}	

	cout << "suff = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (auto j : suff[i])
			cout << j.l << " " << j.r << " " << j.flag << endl; 
		cout << endl;
	}*/


	dfs_up(0, event(-INF, INF, true));
}

void write() {
	for (int i = 0; i < n; i++)
		cout << ans[i] << " ";
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