#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXX = 1e6 + 10;

int lp[MAXX];
vector<int> p;

void precalc() {
	for (int i = 2; i < MAXX; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			p.push_back(i);
		}
		for (int j = 0; j < (int)p.size() && p[j] <= lp[i] && p[j] * i < MAXX; j++) {
			lp[p[j] * i] = p[j];
		}
	}
}

int n, m;

vector<pair<int, int>> have[MAXX];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			while (lp[x]) {
				have[lp[x]].push_back({i, j});
				int a = lp[x];
				while (x % a == 0) {
					x /= a;
				}
			}
		}
	}
}

const int MAXN = 1e3 + 10;

ll ans;

int dp[MAXN][MAXN];

struct event{
	int h, pos, len;
	event() {}
	event(int _h, int _pos, int _len) {
		h = _h, pos = _pos, len = _len;
	}
};

void solve(int num) {
	if (have[num].empty()) return;
	int add = 0;
	int last_x = -1, last_y = -1;
	vector<event> st;
	ll now = 0;
	int len = 0;
	for (auto [x, y] : have[num]) {
		if (x != last_x || y != last_y + 1) { 
			st.clear(), now = 0, len = 1;
		}
		if (x > 0) dp[x][y] = dp[x - 1][y] + 1;
		else dp[x][y] = 1;
		while (!st.empty() && st.back().h >= dp[x][y]) {
			now -= st.back().len * st.back().h;
			st.pop_back();
		}
		if (st.empty()) {
			st.push_back({dp[x][y], y, len});
		} else {
			st.push_back({dp[x][y], y, y - st.back().pos});
		}
		now += st.back().h * st.back().len;
		ans += now;
		add += now;
		last_x = x;
		last_y = y;
		len++;
	}
	for (auto [x, y] : have[num]) {
		dp[x][y] = 0;
	}
}

void run() {
	ans = 0;
	for (int i = 0; i < MAXX; i++) {
		solve(i);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	precalc();
	read();
	run();
	write();
	return 0;
}