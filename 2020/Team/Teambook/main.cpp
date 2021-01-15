#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()



const int MAXN = 1e5 + 10;
int n;
ll a[MAXN], b[MAXN];
ll dp[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];

	Li_chao help = Li_chao();
	help.add(line(b[1], 0));
	for (int i = 2; i <= n; i++) {
		dp[i] = help.get(a[i]);
		help.add(line(b[i], dp[i]));
		//for (int j = 1; j < i; j++) {
		//	dp[i] = min(dp[i], dp[j] + a[i] * b[j]);
		//}
	}

	cout << dp[n] << endl; 
	return 0;
}