#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int INF = 1e18;

struct line {
	int k, b;
	line()
	{
		k = INF;
		b = INF;
	}
	line(int a1, int b1)
	{
		k = a1;
		b = b1;
	}
};

double cross(line a, line b)
{
	return (double) (b.b - a.b)/(a.k - b.k);
}

struct cht {
	vector <line> l;
	vector <double> p;

	cht() {
		l = {};
		p = {};
	}

	void add(line a) {
		while (!p.empty() && cross(l.back(), a) <= p.back())
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
const int MAXN = 1e6 + 10;
int n;
int dp[MAXN], x[MAXN], a[MAXN], b[MAXN];
cht help;
signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> x[i] >> a[i] >> b[i];
	dp[1] = x[1]*b[1] + a[1];
	help.add(line(-x[1], dp[1]));
	for (int i = 2; i <= n; i++)
	{
		dp[i] = min(help.get(b[i]), 0LL) + b[i] * x[i] + a[i];
		help.add(line(-x[i], dp[i]));
	}
	for (int i = 1; i <= n; i++)
	{
		cout << dp[i] << '\n';
	}
	return 0;
}