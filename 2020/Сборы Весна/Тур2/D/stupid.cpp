#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;

int n, w, q;
vector<int> a;

void read() {
	cin >> n >> w >> q;
	a.resize(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

const int INF = 2e9 + 228;

struct node{
	int mn, mx;
	node() {
		mn = INF, mx = -INF;
	}
	node(int a) {
		mn = a, mx = a;
	}
	node(int _mn, int _mx) {
		mn = _mn, mx = _mx;
	} 
};

node merge(const node & a, const node & b) {
	node ans(min(a.mn, b.mn), max(a.mx, b.mx));
	return ans;
}

const int MAXLOG = 17;

struct sparce_table{
	int n;
	vector<vector<node>> sparce;
	vector<int> lg;
	//vector<node> sparce;
	sparce_table() {}

	void build(vector<int> a) {
		sparce.resize(n, vector<node> (MAXLOG, node()));
		lg.resize(n + 1);
		lg[0] = 0;
		lg[1] = 0;
		for (int i = 2; i <= n; i++) {
			lg[i] = lg[i / 2] + 1;
		}
		for (int i = 0; i < n; i++)
			sparce[i][0] = node(a[i]);
		for (int l = 1; l < MAXLOG; l++) {
			for (int i = 0; i + (1 << l) <= n; i++) {
				sparce[i][l] = merge(sparce[i][l - 1], sparce[i + (1 << (l - 1))][l - 1]);
			}
		}
	}

	sparce_table(vector<int> a) {
		n = a.size();
		build(a); 
	}

	node Get(int l, int r) {
		return merge(sparce[l][lg[r - l]], sparce[r - (1 << lg[r - l]) + 1][lg[r - l]]);
	}

	int get(int pos, int k) {
		int l = pos, r = n;
		while (l < r - 1) { 
			int mid = (l + r) / 2;
			node have = Get(pos, mid);
			if (w - k < have.mx - have.mn) {
				r = mid;
			}
			else {
				l = mid;
			}
		}
		return l + 1;
	}
};

sparce_table sparce;

int solve(int k) {
	int ans = -1;
	int pos = 0;
	while (pos < n) { 
		pos = sparce.get(pos, k);
		ans++;
	}
	return ans;
}

int stupid_solve(int k) {
	int l = -INF, r = INF;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		chkmax(l, a[i]);
		chkmin(r, a[i] + w - 1);
		if (r - l + 1 < k) {
			ans++;
			l = a[i];
			r = a[i] + w - 1;
		}
	}
	return ans;
}

void run() {
	sparce = sparce_table(a);
	int BUBEN = 10000;
	while (q--) {
		int k;
		cin >> k;
		if (n <= BUBEN)
			cout << stupid_solve(k) << "\n";
		else
			cout << solve(k) << "\n";
	}
}

void write() {

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