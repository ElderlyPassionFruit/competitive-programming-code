#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int INF = 1e18;

struct line {
	int k, b;
	line() {
		k = 0;
		b = INF;
	}
	line(int k1, int b1) {
		k = k1, b = b1;
	}
};

double cross(line a, line b) {
	return (double) (b.b - a.b) / (a.k - b.k);
}

struct cht {
	vector <double> p;
	vector <line> l;

	cht() {
		p = {};
		l = {};
	}

	void add(line a) {
		while (!p.empty() && cross(a, l.back()) <= p.back())
			p.pop_back(), l.pop_back();
		l.push_back(a);
		if (l.size() >= 2)
			p.push_back(cross(l[l.size() - 1], l[l.size() - 2]));
	}

	int get(int x) {
		int i = lower_bound(p.begin(), p.end(), x) - p.begin();
		return l[i].k * x + l[i].b;
	}
};

const int MAXN = 1e5 +	10;

int n;
int dp[MAXN], a[MAXN], b[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
}

cht help;
void run() {
	dp[1] = 0;
	help.add(line(b[1], dp[1]));
	for (int i = 2; i <= n; i++) {
		dp[i] = help.get(a[i]);
		help.add(line(b[i], dp[i]));
	}
}

void write() {
	cout << dp[n] << endl;	
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("lumber.in", "r", stdin);
	freopen("lumber.out", "w", stdout);
	read();
	run();
	write();
	return 0;
}