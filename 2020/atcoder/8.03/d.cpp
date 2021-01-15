#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct event{
	int a, b;
	event() {}
};

int n, t;
vector<event> a;

void read() {
	cin >> n >> t;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.a >> i.b;
	}
}

vector<int> zero;

void build() {
	vector<event> na;
	for (auto i : a) {
		if (i.a == 0) {
			zero.push_back(i.b);
		}
		else {
			na.push_back(i);
		}
	}
	sort(all(na), [&] (event i, event j) {return j.a * (i.b + 1) < i.a * (j.b + 1);});
	a = na;
	sort(all(zero));
	for (auto &i : zero)
		i++;
	for (int i = 1; i < zero.size(); i++) {
		zero[i] += zero[i - 1];
	}
}

const int MAXLOG = 32;
const int INF = 1e18;
int dp[MAXLOG];

void calc_dp() {
	for (int i = 0; i < MAXLOG; i++)
		dp[i] = t + 1;
	dp[0] = 0;
	for (auto i : a) {
		for (int j = MAXLOG - 1; j >= 1; j--) {
			if (dp[j - 1] == INF) continue;
			int n_time = (i.a + 1) * (dp[j - 1] + 1) + i.b;
			chkmin(dp[j], n_time);
		}
	}
}

int ans;

void run() {
	build();
	calc_dp();
	ans = 0;
	for (int i = 0; i < MAXLOG; i++) {
		int have = dp[i];
		if (have > t) continue;
		int cnt = --upper_bound(all(zero), t - have) - zero.begin() + 1;
		chkmax(ans, i + cnt);
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