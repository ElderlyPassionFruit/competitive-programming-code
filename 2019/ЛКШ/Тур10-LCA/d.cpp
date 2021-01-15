#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 25001;
int par[MAXN], sz[MAXN], st[MAXN];
unsigned int arr[MAXN], fans[MAXN];
vector<int> q[MAXN];

void make(int n) {
	for (int i = 0; i < n; i++) {
		par[i] = i;
		sz[i] = 1;
		fans[i] = arr[i];
		q[i].clear();
	}
}

int get_par(int v) {
	if (v == par[v])
		return v;
	return par[v] = get_par(par[v]);
}

unsigned int get_min(int v) {
	return fans[get_par(v)];
}

void union_set(int v, int u) {
	v = get_par(v);
	u = get_par(u);
	if (v == u)
		return;
	if (sz[v] < sz[u])
		swap(v, u);
	sz[v] += sz[u];
	par[u] = v;
	chkmin(fans[v], fans[u]);
}

void solve(int n, int m, long long a, long long b) {
	for (int i = 1; i <= n; i++) {
		arr[i - 1] = a * i + b;
	}
	
	make(n);
	
	for (int i = n + 1; i <= 2 * m + n; i += 2) {
		unsigned int l = a * i + b;
		l %= n;
		unsigned int r = a * (i + 1) + b;
		r %= n;
		if (l > r)
			swap(l, r);
		q[r].push_back(l); 
	}

	long long ans = 0;
	int pos = -1;
	for (int i = 0; i < n; i++) {
		while (pos >= 0 && fans[st[pos]] > arr[i]) {
			union_set(st[pos], i);
			pos--;
		}
		for (auto j : q[i]) {
			ans += get_min(j);
		}
		pos++;
		st[pos] = i;
	}

	cout << ans << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, a, b;
	while (cin >> n >> m >> a >> b) {
		if (!n && !m && !a && !b)
			break;
		solve(n, m, a, b);
	}
	return 0;
}