#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18;
struct line {
	int k, b;
	line() {
		k = 0, b = INF;
	}
	line(int x, int y) {
		k = x;
		b = y;
	}
};

double cross(line a, line b) {
	return (double) (b.b - a.b) / (a.k - b.k);
}

struct cht {
	vector <double> p;
	vector <line> l;

	cht() {
		l = {}, p = {};
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
		return l[i].k*x + l[i].b;
	}
};

vector <pair <int, int> > start, fans;
int n;

void read() {
	cin >> n;
	start.resize(n);
	for (int i = 0; i < n; i++) 
		cin >> start[i].first >> start[i].second;
	sort(start.begin(), start.end());	
	reverse(start.begin(), start.end());
	fans.push_back(start[0]);
	for (int i = 1; i < n; i++) {
		if (start[i].second > fans.back().second)
			fans.push_back(start[i]);
	}
	reverse(fans.begin(), fans.end());
}

cht help;
const int MAXN = 5*1e4 + 10;
int dp[MAXN];

void run() {
	dp[0] = fans[0].first * fans[0].second;
	help.add(line(fans[0].second, 0));
	for (int i = 1; i < fans.size(); i++) {
		help.add(line(fans[i].second, dp[i - 1]));
		dp[i] = help.get(fans[i].first);
	}
}

void write() {
	cout << dp[fans.size() - 1] << endl;
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