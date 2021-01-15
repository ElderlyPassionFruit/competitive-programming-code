#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const long long INF = 1e18 + 10;

struct line{
	long long k, b;
	line() {
		k = 0, b = INF;
	}
	line(long long x, long long y) {
		k = x, b = y;
	}
};

long long eval(line l, long long x) {
	return l.k * x + l.b;
}

double cross(line l, line m) {
	return (double) (m.b - l.b) / (l.k - m.k);
}

struct cht{
	vector<double> p;
	vector<line> l;

	cht() {
		l = {};
		p = {};
	}

	void add(line x) {
		while (!p.empty() && cross(l.back(), x) <= p.back())
			p.pop_back(), l.pop_back();
		l.push_back(x);
		if (l.size() >= 2) {
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
		}	
	}

	long long get(long long x) {
		long long pos = lower_bound(p.begin(), p.end(), x) - p.begin();
		return eval(l[pos], x);
	}
};

const long long MAXN = 1e5 + 10;
long long a[MAXN], b[MAXN];
long long n;

void read() {
	cin >> n;
	for (long long i = 1; i <= n; i++)
		cin >> a[i];
	for (long long i = 1; i <= n; i++)
		cin >> b[i];
}

long long dp[MAXN];
long long ans;

void run() {
	cht help;
	dp[1] = 0;
	help.add(line(b[1], 0));
	for (long long i = 2; i <= n; i++) {
		dp[i] = help.get(a[i]);
		help.add(line(b[i], dp[i]));
	}
	ans = dp[n];
}

void write() {
	cout << ans << endl;
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