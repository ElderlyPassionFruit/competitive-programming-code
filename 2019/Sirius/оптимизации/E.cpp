#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 1e18;
struct line{
	int k, b;
	line() {
		k = 0, b = INF;
	}
	line(int x, int y) {
		k = x, b = y;
	}
};

double cross(line a, line b) {
	return (double) (b.b - a.b) / (a.k - b.k);
}

struct cht{
	vector <double> p;
	vector <line> l;

	cht() {
		p = {}, l = {};
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


const int MAXN = 1e5 + 10, MAXP = 110;
int d[MAXN], event[MAXN], dp[MAXN][MAXP], cat[MAXN][2];
int pref[MAXN];
int n, m, p;
int fans = 0;
void read() {
	cin >> n >> m >> p;
	for (int i = 2; i <= n; i++)
		cin >> d[i];
	for (int i = 2; i <= n; i++) 
		d[i] = d[i - 1] + d[i];

	for (int i = 1; i <= m; i++)
		cin >> cat[i][0] >> cat[i][1];
	for (int i = 1; i <= m; i++) {
		event[i] = cat[i][1] - d[cat[i][0]];
	}
	sort(event + 1, event + m + 1);             
	for (int i = 0; i < MAXN; i++) {
		if (event[i] >= 0) break;
		fans += abs(event[i]);
		event[i] = 0;
	}
}

cht help[MAXP];

int pref_event[MAXN];
void run() {
	for (int i = 1; i <= m; i++)
		pref_event[i] = pref_event[i - 1] + event[i];

	for (int i = 1; i <= m; i++) {
		dp[i][1] = event[i] * i - pref_event[i];
		for (int j = 2; j <= min(i, p); j++) {
			dp[i][j] = INF;
			
			dp[i][j] = help[j - 1].get(event[i]) + i * event[i] - pref_event[i];
		}
		for (int j = 1; j <= min(i, p); j++)
			help[j].add(line(-i, dp[i][j] + pref_event[i]));
	}
}

void write() {
	int ans = 1e18;
	for (int i = 1; i <= p; i++)
		ans = min(ans, dp[m][i]);
	cout << ans + fans << endl;
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