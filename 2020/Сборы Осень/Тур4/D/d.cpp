#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int INF = 1e9 + 10;

const int MAXN = 210;
int dp[MAXN][MAXN];
bool check[MAXN][MAXN];
int par[MAXN][MAXN];
int par_del[MAXN][MAXN];
int tree[MAXN];
int n;

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
			check[i][j] = false;
			par[i][j] = -1;
			par_del[i][j] = -1;
		}
	}
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> tree[i];
}

bool Check(int l, int r, int m) {
	if (tree[l] < tree[m] && tree[r] < tree[m]) return true;
	if (tree[l] > tree[m] && tree[r] > tree[m]) return true;
	return false;
}

void calc_Check() {
	for (int r = 0; r < n; r++) {
		for (int l = r; l >= 0; l--) {
			check[l][r] = false;
			par_del[l][r] = -1;
			if (r - l + 1 <= 2) {
				check[l][r] = true;
				continue;
			}
			for (int m = l + 1; m <= r - 1; m++) {
				if (check[l][m] && check[m][r] && Check(l, r, m)) {
					check[l][r] = true;
					par_del[l][r] = m;
				}
			}
		}
	}
}

void calc_dp() {
	for (int r = 0; r < n; r++) {
		for (int l = r; l >= 0; l--) {
			dp[l][r] = INF;
			par[l][r] = -1;
			if (tree[l] > tree[r]) continue;
			if (l == r) {
				dp[l][r] = 0;
				par[l][r] = -1;
			}
			if (check[l][r] && r > l) {
				dp[l][r] = r - l - 1;
				par[l][r] = par_del[l][r];
			}

			for (int m = l + 1; m <= r - 1; m++) {
				if (tree[l] <= tree[m] && tree[m] <= tree[r]) {
					if (dp[l][r] > dp[l][m] + dp[m][r]) {
						dp[l][r] = dp[l][m] + dp[m][r];
						par[l][r] = m;
					}
				}
			}
		}
	}
}

void calc() {
	build();
	calc_Check();
	calc_dp();
}

vector<int> ans;

void del(int l, int r) {
	if (par_del[l][r] == -1) return;
	ans.push_back(par_del[l][r]);
	del(l, par_del[l][r]);
	del(par_del[l][r], r);
}

void make_ans(int l, int r) {
	if (par[l][r] == -1) return;
	if (dp[l][r] == r - l - 1) {
		del(l, r);
	}
	else {
		make_ans(l, par[l][r]);
		make_ans(par[l][r], r);
	}
}

void make_ans() {
	if (dp[0][n - 1] == INF) {
		cout << -1 << endl;
		exit(0);
	}
	make_ans(0, n - 1);
}

void run() {
	calc();
	make_ans();
}

void write() {
	reverse(all(ans));
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i + 1 << "\n";
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