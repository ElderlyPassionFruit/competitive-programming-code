#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,mmx,avx2,popcnt")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r;
	segment() {}
	segment(int a, int b) {
		l = a, r = b;
	}
};

struct event{
	segment a;
	int v;
	event() {}
	event(segment x, int y) {
		a = x, v = y;
	}
};

const int MAXN = 1e6 + 10;
int n, k;
vector<int> g[MAXN];
vector<segment> have[MAXN];

void read() {
	scanf("%d%d",&n,&k);
	for (int i = 0; i < n; i++) {
		have[i].resize(k);
		for (int j = 0; j < k; j++){
			scanf("%d",&have[i][j].l);
		}
		for (int j = 0; j < k; j++){
			scanf("%d",&have[i][j].r);
		}
		for (int j = 0; j < k; j++) {
			if (have[i][j].l > have[i][j].r) swap(have[i][j].l, have[i][j].r);
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d%d",&u,&v);
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

bool used[MAXN];
int sz[MAXN];
int centr;

void dfs_centr(int v, int p, int size) {
	sz[v] = 1;
	int mx = 0;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_centr(i, v, size);
			sz[v] += sz[i];
			chkmax(mx, sz[i]);
		}
	}
	chkmax(mx, size - sz[v]);
	if (mx <= size / 2) {
		centr = v;
	}
}

int ans;
const int INF = 1e9;
int nxt[MAXN];
int dist[MAXN];

void recalc(const vector<int> & l, const vector<int> & r, int ind) {
	int fans = INF;
	int pos = 0;
	//cout << "puhh" << endl;
	for (auto i : l) {
		while (pos < r.size() && have[r[pos]][ind].r < have[i][ind].l) {
			chkmin(fans, dist[r[pos]]);
			pos++;
		}
		chkmin(ans, fans + dist[i]);
	}
	//cout << "puhh" << endl;
}

void dfs_color(int v, int p, int color, int len) {
	nxt[v] = color;
	dist[v] = len++;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_color(i, v, color, len);
		}
	}
}

void solve(int v, int size, int ind, int len, vector<int> & l, vector<int> & r) {
	assert(len < 20);
	dfs_centr(v, -1, size);
	v = centr;
	//cout << "v = " << v << endl;
	used[v] = true;
	dist[v] = 0;
	int cnt = 0;
	for (auto i : g[v]) {
		if (!used[i]) {
			dfs_color(i, v, cnt, 1);	
			cnt++;
		}
	}

	/*cout << "l = " << endl;
	for (auto i : l)
		cout << i << " ";
	cout << endl;
	cout << "r = " << endl;
	for (auto i : r)
		cout << i << " ";
	cout << endl << endl;
	
	cout << "nxt = " << endl;*/
	recalc(l, r, ind);
	
	vector<vector<int> > nl(cnt), nr(cnt);
	for (auto i : l) {
		if (i == v) continue;
		nl[nxt[i]].push_back(i);
	}

	for (auto i : r) {
		if (i == v) continue;
		nr[nxt[i]].push_back(i);
	}

	cnt = 0;
	for (auto i : g[v]) {
		if (!used[i]) {
			int fsz = sz[i];
			if (sz[i] > sz[v])
				fsz = size - sz[v];
			assert(nl.size() > cnt);
			solve(i, fsz, ind, len + 1, nl[cnt], nr[cnt]);
			cnt++;
		}
	}
}

void solve(int ind, vector<int> & l, vector<int> & r) {
	for (int i = 0; i < n; i++)
		used[i] = false;
	solve(0, n, ind, 0, l, r);
}

void wr() {
	cout << "have = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i = " << i << endl;
		for (int j = 0; j < k; j++) {
			cout << have[i][j].l << " " << have[i][j].r << endl;
		}
		cout << endl;
	}

	cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		cout << "i =  " << i << endl;
		cout << "ed = ";
		for (auto j : g[i]) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void run() {
	ans = n + 1;
	vector<int> l(n), r(n);
	for (int j = 0; j < n; j++) {
		l[j] = j, r[j] = j;
	}	
	for (int i = 0; i < k; i++) {
		sort(all(l), [&] (int a, int b) {return have[a][i].l < have[b][i].l;});
		sort(all(r), [&] (int a, int b) {return have[a][i].r < have[b][i].r;});
		solve(i, l, r);
	}
	if (ans == n + 1)
		ans = -1;
}	

void write() {
	cout << ans << endl;
}

signed main() {
	read();
	run();
	write();
	return 0;
}