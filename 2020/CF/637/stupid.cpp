#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, m;
vector<int> d;
int g, r;

void read() {
	cin >> n >> m;
	d.resize(m);
	for (auto &i : d) {
		cin >> i;
	}
	sort(all(d));
	cin >> g >> r;
}

const int INF = 1e18;
vector<vector<int>> dp;

struct event{
	int pos, val, len;
	event() {}
	event(int _pos, int _val, int _len) {
		pos = _pos, val = _val, len = _len;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.len, a.pos, a.val) < tie(b.len, b.pos, b.val);
}

set<event> q;
int ans;

void calc() {
	dp.assign(m, vector<int> (g + 1, INF));
	dp[0][0] = 0;
	q.insert({0, 0, 0});
	while (!q.empty()) {
		int pos = q.begin()->pos;
		int val = q.begin()->val;
		q.erase(q.begin());
		for (int i = 0; i < m; i++) {
			if (i == pos) continue;
			int len = abs(d[i] - d[pos]);
			if (val + len > g) continue;
			if (dp[i][val + len] <= dp[pos][val] + len) continue;
			q.erase({i, val + len, dp[i][val + len]});
			dp[i][val + len] = dp[pos][val] + len;
			q.insert({i, val + len, dp[i][val + len]});
		} 
		if (val == g) {
			if (dp[pos][0] > dp[pos][val] + r) {
				q.erase({pos, 0, dp[pos][0]});
				dp[pos][0] = dp[pos][val] + r;
				q.insert({pos, 0, dp[pos][0]});
			}
		}
	}
	
	for (int i = 0; i <= g; i++) {
		chkmin(ans, dp[m - 1][i]);
	}
}

void run() {
	ans = INF;
	calc();
	if (ans == INF) {
		ans = -1;
	}
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