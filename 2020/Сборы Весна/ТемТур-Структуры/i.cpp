#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXM = 3e5 + 10;
const int MAXN = 5e4 + 10;
const int MAXD = 50;
const ll INF = -1e18 - 228 - 1337;
int D;
int a[MAXN], b[MAXN], c[MAXN];
int modA[MAXN], modB[MAXN], modC[MAXN];
int n;

struct query{
	int l, r, ind;
	query() {}
	query(int _l, int _r, int _ind) {
		l = _l, r = _r, ind = _ind;
	}
};

struct node{
	ll dp[MAXD];
	int sz = 0;
	node() {
		for (int i = 0; i < D; i++) {
			dp[i] = INF;
			sz = 0;
		}
	}
	node(int a, int b, int c) {
		for (int i = 0; i < D; i++) {
			dp[i] = INF;
		}
		chkmax(dp[a % D], a);
		chkmax(dp[b % D], b);
		chkmax(dp[c % D], c);
		sz = 1;
	}
};

node add(node x, int ind) {
	node ans = node();
	for (int i = 0; i < D; i++) {
		if (x.dp[i] == INF) continue;
		int nxt;
		nxt = i + modA[ind];
		if (nxt >= D) nxt -= D;
		chkmax(ans.dp[nxt], x.dp[i] + a[ind]);
		nxt = i + modB[ind];
		if (nxt >= D) nxt -= D;
		chkmax(ans.dp[nxt], x.dp[i] + b[ind]);
		nxt = i + modC[ind];
		if (nxt >= D) nxt -= D;
		chkmax(ans.dp[nxt], x.dp[i] + c[ind]);
	}
	ans.sz = x.sz + 1;
	return ans;
}

ll ans[MAXM];
node L[MAXN];
node R[MAXN];

void solve(int l, int r, vector<query> q) {
	if (r < l) return;
	if (q.empty()) return; 
	vector<query> ql, qr, qnow;
	int m = (l + r) / 2;
	R[0] = node(a[m], b[m], c[m]);
	for (int i = m + 1; i <= r; i++)
		R[i - m] = add(R[i - m - 1], i);
	if (l < m) {
		L[0] = node(a[m - 1], b[m - 1], c[m - 1]);
		for (int i = m - 2; i >= l; i--){
			L[m - 1 - i] = add(L[m - 1 - i - 1], i);
		} 
	}	
	for (auto i : q) {
		if (i.r < m) {
			ql.push_back(i);
		} else if (i.l > m) {
			qr.push_back(i);
		} else {
			if (i.l == m) {
				ans[i.ind] = R[i.r - m].dp[0];
			} else {
				ans[i.ind] = INF;
				for (int x = 0; x < D; x++) {
					int y = D - x;
					if (y == D) y = 0;
					if (L[m - 1 - i.l].dp[x] != INF && R[i.r - m].dp[y] != INF) {
						chkmax(ans[i.ind], L[m - 1 - i.l].dp[x] + R[i.r - m].dp[y]);
					}
				}
			}
			if (ans[i.ind] == INF)
				ans[i.ind] = -1;
		}
	}
	if (l <= m - 1) {
		solve(l, m - 1, ql);
	}
	if (m + 1 <= r) {
		solve(m + 1, r, qr);
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> D;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> c[i];
		modA[i] = a[i] % D;
		modB[i] = b[i] % D;
		modC[i] = c[i] % D;
	}
	int q;
	cin >> q;
	vector<query> have;
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		have.push_back({l, r, i});
	}
	
	solve(0, n - 1, have);
	for (int i = 0; i < q; i++)
		cout << ans[i] << "\n";
	return 0;
}