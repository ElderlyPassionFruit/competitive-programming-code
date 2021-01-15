#include <bits/stdc++.h>

using namespace std;

int n, v;
const int MAXN = 1e5 + 10;
vector<pair <int, int> > a;

int bg;

void read() {
	bg = clock();
	cin >> n;
	a.assign(n + 1, {0, 0});
	for (int i = 1; i <= n; i++)
		cin >> a[i].second >> a[i].first;
	sort(a.begin() + 1, a.end());
	cin >> v;
}


int dp[MAXN];

void clear() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = 0;
}

int ans1, ans2;

void run() {

	clear();
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++) {

			int have = a[i].first - a[j].first;
			int need = (abs(a[i].second - a[j].second) + v - 1) / v;
			if (have >= need && (dp[j] > 0 || j == 0)) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}

	ans1 = 0;
	for (int i = 1; i <= n; i++)
		ans1 = max(ans1, dp[i]);


	clear();
	for (int i = 1; i <= n; i++) {
		dp[i] = 1;
		for (int j = 1; j < i; j++) {
			int have = a[i].first - a[j].first;
			int need = (abs(a[i].second - a[j].second) + v - 1) / v;
			if (have >= need) {
				dp[i] = max(dp[i], dp[j] + 1);
			}	
		}
	}

	ans2 = 0;
	for (int i = 1; i <= n; i++)
		ans2 = max(ans2, dp[i]);
}

void write() {
	cout << ans1 << " " << ans2 << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}