#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 110;
int n;
int s[MAXN];

const int INF = 1e9 + 228;
const int MAXM = 20;
int dp[2][1 << MAXM];	
int m;

char type[MAXM];
int t[MAXM];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	sort(s, s + n);
	reverse(s, s + n);
	/*cout << "s = " << endl;
	for (int i = 0; i < n; i++) {
		cout << s[i] << " ";
	}
	cout << endl;*/
	int m;
	cin >> m;
	n = min(n, m);

	for (int i = 0; i < m; i++) {
		cin >> type[i] >> t[i];
	}

	/*cout << "t = " << endl;
	for (int i = 0; i < m; i++) {
		cout << t[i] << " ";
	}
	cout << endl;*/

	/*cout << "dp = " << endl;
	for (int mask = 0; mask < (1 << n); mask++) {
		cout << dp[1][mask] << " ";
	}
	cout << endl;*/

	for (int i = m - 1; i >= 0; i--) {
		for (int mask = 0; mask < (1 << n); mask++) {
			int mnVal = INF, mxVal = -INF;
			if (type[i] == 'b') {
				mnVal = min(mnVal, dp[0][mask]);
				mxVal = max(mxVal, dp[0][mask]);
			}
			for (int bit = 0; bit < n; bit++) {
				if ((mask >> bit) & 1) continue;
				if (type[i] == 'b') {
					mnVal = min(mnVal, dp[0][mask ^ (1 << bit)]);
					mxVal = max(mxVal, dp[0][mask ^ (1 << bit)]);
				} else {
					//cout << "i = " << i << " t[i] = " << t[i] << " " << (t[i] == 1) << " " << (t[i] == 1 ? s[bit] : -s[bit]) << endl;
					mnVal = min(mnVal, dp[0][mask ^ (1 << bit)] + (t[i] == 1 ? s[bit] : -s[bit]));
					mxVal = max(mxVal, dp[0][mask ^ (1 << bit)] + (t[i] == 1 ? s[bit] : -s[bit]));
				}
			}
			//cout << "i = " << i << " mask = " << mask << " mnVal = " << mnVal << " mxVal = " << mxVal << endl;
			if (t[i] == 1) {
				dp[1][mask] = mxVal;
			} else {
				dp[1][mask] = mnVal;
			}
		}
		/*cout << "i = " << i << endl;
		cout << "dp = " << endl;
		for (int mask = 0; mask < (1 << n); mask++) {
			cout << dp[1][mask] << " ";
		}
		cout << endl;*/
		for (int mask = 0; mask < (1 << n); mask++) {
			dp[0][mask] = dp[1][mask];
		}
	}
	cout << dp[0][0] << endl;
	return 0;
}
