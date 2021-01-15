#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,tune=native,avx,avx2,mmx")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
using ld = long double;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = -1e18;

struct line{
	int k, b;
	line() {
		k = 0, b = INF;
	}
	line(int x, int y) {
		k = x, b = y;
	}
};

int eval(line l, int x) {
	return l.k * x + l.b;
}

ld cross(line l, line m) {
	return (ld) (l.b - m.b) / (m.k - l.k);
}

struct cht{
	vector<line> l;
	vector<ld> p;
	cht() {
	}

	void add(line x) {
		if (!l.empty() && l.back().k == x.k) {
			if (l.back().b >= x.b) return;
			l.pop_back();
		}
		while (!p.empty() && p.back() >= cross(l.back(), x))
			l.pop_back(), p.pop_back();
		l.push_back(x);
		if (l.size() >= 2) {
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
		}
	}

	int get(int x) {
		if (l.empty()) return INF;
		int pos = lower_bound(all(p), x) - p.begin();
		return eval(l[pos], x);
	}
};

const int MAXN = 4e3 + 10, MAXK = 8e2 + 10;
int n, k;
int a[MAXN];
int dp[MAXN][MAXK];
cht help[MAXK];

void read() {
	cin >> n >> k;
	k = min(k, n);
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
}

void calc() {
	sort(a + 1, a + n + 1);
	help[0].add(line(a[1], 0));
	for (int i = 1; i <= n; i++) {
		for (int j = k; j >= 1; j--) {
			int x = help[j - 1].get(i);
			if (x == INF) continue;
			dp[i][j] = x;
			help[j].add(line(a[i + 1], dp[i][j] - a[i + 1] * i));
		}
		help[0].add(line(a[i + 1],- a[i + 1] * i));
	}
}

void calc2() {
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = k; j >= 1; j--) {
			dp[i][j] = INF;
			for (int x = 0; x < i; x++) {
				chkmax(dp[i][j], dp[x][j - 1] + a[x + 1] * (i - x));
			}
		}
	}
}

void run() {
	calc();
}

void write() {
	cout << dp[n][k] << endl;
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