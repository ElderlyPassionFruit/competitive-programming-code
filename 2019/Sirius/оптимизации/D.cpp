#include <bits/stdc++.h>

using namespace std;

#define int long long

struct line{
	int k, b;
	line() {
		k = 0, b = 1e18;
	}
	line (int x, int y) {
		k = x;
		b = y;
	}
};

int eval(line a, int x) {
	return a.k * x + a.b;
}

double cross(line a, line b) {
	return (long double)(b.b - a.b) / (a.k - b.k);
}

struct cht{
	vector <double> p;
	vector <line> l;

	cht() {
		p = {};
		l = {};
	}

	void add(line a) {
		while (!p.empty() && cross(l.back(), a) <= p.back())
			p.pop_back(), l.pop_back();
		l.push_back(a);
		if (l.size() >= 2) {
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
		}
	}

	int get(int x) {
		int i = lower_bound(p.begin(), p.end(), x) - p.begin();
		return eval(l[i], x);
	}
};

const int MAXN = 1e5 + 10;
int a[MAXN], b[MAXN], dp[MAXN];
int n;
cht help;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
}

void run() {
	dp[0] = 0;
	help.add(line(b[0], dp[0]));
	for (int i = 1; i < n; i++) {
		dp[i] = help.get(a[i]);
		help.add(line(b[i], dp[i]));
	}
}

void write() {
	cout << dp[n - 1];
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