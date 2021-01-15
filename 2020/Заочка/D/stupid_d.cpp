#include <bits/stdc++.h>

using namespace std;
//#define int long long
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

bool operator<(const segment & a, const segment & b) {
	return tie(a.l, a.r) < tie(b.l, b.r); 
}

struct event{
	segment a;
	int len;
	event() {}
	event(segment x, int y) {
		a = x, len = y;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.a, a.len) < tie(b.a, b.len);
}

segment merge(const segment & a, const segment & b) {
	segment ans;
	ans.l = max(a.l, b.l);
	ans.r = min(a.r, b.r);
	return ans;
}

bool check(const segment & a) {
	return a.l > a.r;
}

const int MAXN = 1e2 + 10;
int n, k;
vector<int> g[MAXN];
vector<segment> have[MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		have[i].resize(k);
		for (int j = 0; j < k; j++) {
			cin >> have[i][j].l;
		}
		for (int j = 0; j < k; j++) {
			cin >> have[i][j].r;
		}
		for (int j = 0; j < k; j++) {
			if (have[i][j].l > have[i][j].r) swap(have[i][j].l, have[i][j].r);
		}
 	}
 	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

const int INF = 1e9;
int ans;

void calc(int v, int p, segment now, int len, int ind) {
	now = merge(now, have[v][ind]);
	if (check(now)) {
		ans = min(ans, len);
	}
	len++;
	for (auto i : g[v]) {
		if (i != p) {
			calc(i, v, now, len, ind);
		}
	}
}

void run() {
	ans = INF;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < n; j++) {
			calc(j, -1, have[j][i], 0, i);
		}
	}
	if (ans == INF)
		ans = -1;
}

void write() {
	cout << ans;
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