#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll

int n, k, m;
const int MAXN = 2e5 + 10;
int dp[MAXN];
vector<int> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k >> m;
	a.resize(m);
	for (auto &i : a)
		cin >> i;
	sort(all(a));
	/*for (auto i : a)
		cout << i << " ";
	cout << endl;*/
	int ans = 0;
	for (int i = 0; i < m; i++) {
		dp[i] = a[i];
		int pos = lower_bound(all(a), a[i] - k + 1) - a.begin();
		//cout << i << " " << pos << endl;
		dp[i] = min(dp[i], (pos == 0 ? 0 : dp[pos - 1]) + k);
		if (a[i] >= a[m - 1] - k + 1) {
			ans = max(ans, n - (i > 0 ? dp[i - 1] : 0) - min(n - a[i] + 1, k));
		}
		//cout << dp[i] << endl;
	}
	//cout << endl;
	ans = max(ans, n - dp[m - 1]);
	cout << ans << endl;
	return 0;
}