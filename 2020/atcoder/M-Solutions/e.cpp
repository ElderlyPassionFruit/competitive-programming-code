#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int N = 17;
const int INF = 1e18 + 228;
int n;
int x[N], y[N], p[N];
bool used[N];
int q[N];
int topQ;
int dp[N][N];
int cost[N][N];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i] >> p[i];
	}
}

int calcCost(int L, int R, int mask) {
	if (cost[L][R] != INF) return cost[L][R];
	int ans = 0;
	for (int i = L + 1; i < R; i++) {
		int add = INF;
		int ind = q[i - 1];
		if (L >= 1) {
			int l = q[L - 1];
			chkmin(add, abs(y[ind] - y[l]));
		}
		if (R <= topQ) {
			int r = q[R - 1];
			chkmin(add, abs(y[ind] - y[r]));
		}
		for (int bit = 0; bit < n; bit++) {
			if ((mask >> bit) & 1) {
				chkmin(add, abs(x[ind] - x[bit]));
			}
		}
		chkmin(add, min(abs(x[ind]), abs(y[ind])));
		ans += p[ind] * add;
	}
	cost[L][R] = ans;
	return ans;
}

int calcDp(int k, int mask) {
	if (topQ == 0) return 0;
	if (topQ <= k) return 0;
	sort(q, q + topQ, [&] (int a, int b) {
		return y[a] < y[b];
	});
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dp[i][j] = INF;
			cost[i][j] = INF;
		}
	}
	dp[0][0] = 0;
	for (int pos = 1; pos <= topQ; pos++) {
		for (int cnt = 1; cnt <= min(pos, k); cnt++) {
			for (int prev = 0; prev < pos; prev++) {
				if (dp[prev][cnt - 1] == INF) continue;
				chkmin(dp[pos][cnt], dp[prev][cnt - 1] + calcCost(prev, pos, mask));
			}
		}
	}
	int ans = INF;
	for (int i = 0; i <= topQ; i++) {
		if (dp[i][k] == INF) continue;
		chkmin(ans, dp[i][k] + calcCost(i, topQ + 1, mask));
	}
	return ans;
}

int calc(int mask, int k) {
	k -= __builtin_popcount(mask);
	if (k < 0) return INF;
	fill(used, used + n, false);
	for (int i = 0; i < n; i++) {
		if (x[i] == 0) used[i] = true;
		if (!((mask >> i) & 1)) continue;
		for (int bit = 0; bit < n; bit++) {
			if (x[i] == x[bit]) {
				used[bit] = true;
			}
		}
	}
	topQ = 0;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		q[topQ++] = i;
	}
	return calcDp(k, mask);
}

int solve(int k) {
	int ans = INF;
	for (int mask = 0; mask < (1 << n); mask++) {
		int fans = calc(mask, k);
		chkmin(ans, fans);
	}
	return ans;
}

int ans[N];

void run() {
	for (int i = 0; i <= n; i++) {
		ans[i] = solve(i);
	}
}

void write() {
	for (int i = 0; i <= n; i++) {
		cout << ans[i] << "\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}