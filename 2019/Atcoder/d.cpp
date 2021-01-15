#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;
const int MAXN = 13;
int dp[MAXN];
int Next[MAXN];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	reverse(s.begin(), s.end());
	int n = s.size();

	if (s[0] != '?')
		dp[s[0] - '0'] = 1;
	else 
		for (int i = 0; i <= 9; i++)
			dp[i] = 1;

	int pow = 1;
	for (int i = 1; i < n; i++) {
		pow *= 10;
		pow %= 13;

		if (s[i] != '?') {
			for (int j = 0; j < 13; j++) {
				Next[(j + (s[i] - '0') * pow) % 13] += dp[j];
			}
		}
		else {
			for (int j = 0; j < 13; j++) {
				for (int k = 0; k <= 9; k++) {
					Next[(j + k * pow) % 13] += dp[j];
				}
			}
		}

		for (int i = 0; i < 13; i++) {
			dp[i] = Next[i];
			Next[i] = 0;
			dp[i] %= MOD;
		}
		//cout << "dp = " << endl;
		//for (int i = 0; i < 13; i++)
		//	cout << dp[i] << " ";
		//cout << endl;	
	}

	cout << dp[5] << endl;
	return 0;
}