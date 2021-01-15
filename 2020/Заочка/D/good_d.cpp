#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("section-anchors")
//#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
//#pragma GCC optimize("function-sections")
//#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")
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

const int MAXN = 1e6 + 10;
const int INF = 1e6 + 10;

int n, k;
vector<int> g[MAXN];
vector<segment> have[MAXN];

bool used[MAXN];
int sz[MAXN], centr;

int ans;
int nxt[MAXN], dist[MAXN];
int l[MAXN], r[MAXN];
int fsz[MAXN];
int na[MAXN];
int pref[MAXN];

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

void recalc(int L, int R, int ind) {
	int fans = INF;
	int pos = L;
	for (int j = L; j < R; j++) {
		while (pos < R && have[r[pos]][ind].r < have[l[j]][ind].l) {
			chkmin(fans, dist[r[pos]]);
			pos++;
		}
		chkmin(ans, fans + dist[l[j]]);
	}
}

void bfs_color(int v, int color) {
	vector<pair<int, int> > q;
	q.push_back({v, v});
	dist[v] = 0;
	while (!q.empty()) {
		int v = q.back().first;
		int p = q.back().second;
		q.pop_back();
		nxt[v] = color;
		fsz[color]++;
		for (auto i : g[v]) {
			if (i != p && !used[i]) {
				dist[i] = dist[v] + 1;
				q.push_back({i, v});
			}
		}
	}
}

/*
void dfs_color(int v, int p, int color, int len) {
	nxt[v] = color;
	dist[v] = len++;
	fsz[color]++;
	for (auto i : g[v]) {
		if (i != p && !used[i]) {
			dfs_color(i, v, color, len);
		}
	}
}
*/

void rebuild(int L, int R, int cnt, int v) {
	pref[0] = L;
	for (int i = 1; i <= cnt; i += 4){
		pref[i] = pref[i - 1] + fsz[i - 1];
		pref[i + 1] = pref[i] + fsz[i];
		pref[i + 2] = pref[i + 1] + fsz[i + 1];
		pref[i + 3] = pref[i + 2] + fsz[i + 2];
	}

	for (int i = L; i < R; i++) {
		if (l[i] == v) continue;
		na[pref[nxt[l[i]]]++] = l[i];
	}

	for (int i = L; i + 3 < R; i += 4) {
		l[i] = na[i];
		l[i + 1] = na[i + 1];
		l[i + 2] = na[i + 2];
		l[i + 3] = na[i + 3];
	}

	for (int i = max(L, R - 3); i < R; i++) {
		l[i] = na[i];
	}

	pref[0] = L;
	for (int i = 1; i <= cnt; i += 4){
		pref[i] = pref[i - 1] + fsz[i - 1];
		pref[i + 1] = pref[i] + fsz[i];
		pref[i + 2] = pref[i + 1] + fsz[i + 1];
		pref[i + 3] = pref[i + 2] + fsz[i + 2];
	}

	for (int i = L; i < R; i++) {
		if (r[i] == v) continue;
		na[pref[nxt[r[i]]]++] = r[i];
	}
	
	for (int i = L; i < R; i += 4) {
		r[i] = na[i];
		r[i + 1] = na[i + 1];
		r[i + 2] = na[i + 2];
		r[i + 3] = na[i + 3];
	}

	for (int i = max(L, R - 3); i < R; i++) {
		r[i] = na[i];
	}
}

void solve(int v, int size, int ind, int len, int L, int R) {
	assert(len < 20);
	dfs_centr(v, -1, size);
	v = centr;
	used[v] = true;
	dist[v] = 0;
	nxt[v] = -1;
	int cnt = 0;
	for (auto i : g[v]) {
		if (!used[i]) {
			fsz[cnt] = 0;
			bfs_color(i, cnt);
			//dfs_color(i, v, cnt, 1);	
			cnt++;
		}
	}

	vector<int> x;
	for (int i = 0; i < cnt; i++)
		x.push_back(fsz[i]);


	recalc(L, R, ind);
	rebuild(L, R, cnt, v);
	
	int pos = 0;
	cnt = 0;

	for (auto i : g[v]) {
		if (!used[i]) {
			int Mysz = sz[i];
			if (sz[i] > sz[v])
				Mysz = size - sz[v];
			solve(i, Mysz, ind, len + 1, L + pos, L + pos + x[cnt]);
			pos += x[cnt];
			cnt++;
		}
	}
}

void solve(int ind) {
	for (int i = 0; i < n; i++)
		used[i] = false;
	solve(0, n, ind, 0, 0, n);
}

void run() {
	ans = n + 1;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			l[j] = j, r[j] = j;
		}	
		sort(l, l + n, [&] (int a, int b) {return have[a][i].l < have[b][i].l;});
		sort(r, r + n, [&] (int a, int b) {return have[a][i].r < have[b][i].r;}); 
		solve(i);
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