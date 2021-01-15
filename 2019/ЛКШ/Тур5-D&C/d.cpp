#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, mod;
vector<int> x, y;
void read() {
	cin >> n >> m >> mod;
	x.resize(n);
	for (auto &i : x)
		cin >> i;
	y.resize(m);
	for (auto &i : y)
		cin >> i;
}

pair <int, string> solve(vector<int> start, int pos, int l, int r) {
	vector<vector<int> > dp(r - l + 1, vector<int> (m, 0));
	dp[0] = start;
	vector<vector<int> > par(r - l + 1, vector<int> (m, 0));
	for (int i = 1; i < r - l + 1; i++) {
		for (int j = 0; j < m; j++) {
			dp[i][j] = dp[i - 1][j];
			if (j > 0)
				chkmax(dp[i][j], dp[i][j - 1]);
			if (dp[i][j] == dp[i - 1][j])
				par[i][j] = 1;
			else 
				par[i][j] = 2;
			dp[i][j] += (x[i + l] + y[j]) % mod;
		}
	}

	string ans = "";

	int x = r - l, y = pos;
	while (par[x][y]) {
		if (par[x][y] == 1) {
			ans += "C";
			x--;
		}
		else {
			ans += "S";
			y--;
		}
	}
	return {y, ans};
}
 
pair <int, string> smart() {
	vector<int> dp(m, 0);
	vector<vector<int> > pers_dp;
	int SQRT = max((int)sqrt(n), 1);
	int fans = 0;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (j > 0) 
				chkmax(dp[j], dp[j - 1]);
			dp[j] += (x[i] + y[j]) % mod;	
			chkmax(fans, dp[j]);
		}
		if (i % SQRT == 0) {
			pers_dp.push_back(dp);
		}
	}

	string ans = "";
	int pos = m - 1;
	while (!pers_dp.empty()) {
		int l = (pers_dp.size() - 1) * SQRT;
		int r = min(l + SQRT, n - 1);
		auto fans = solve(pers_dp.back(), pos, l, r);
		pers_dp.pop_back();
		pos = fans.first;
		ans += fans.second;
	}
	while (pos) {
		ans += "S";
		pos--;
	}
	reverse(ans.begin(), ans.end());
	return {fans, ans};
}

pair <int, string> ans;

void run() {
	ans = smart();
}

void write() {
	cout << ans.first << endl;
	cout << ans.second << endl;
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


/*
2 2 10
0 0
0 1

3 3 10
0 2 0
0 0 2

3 3 2
0 1 1
1 1 0
*/