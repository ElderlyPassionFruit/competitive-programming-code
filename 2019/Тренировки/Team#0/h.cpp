#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long double ld;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;
	vector<vector<ld>> dp(n+1, vector<ld> (n+1));
	dp[n][n] = 1;
	for(int i = n;i >=0;--i)
	{
		for(int j = n; j>=0;--j)
		{
			if(i > 0)
				dp[i-1][j] += dp[i][j] * 0.5;
			if(j > 0)
				dp[i][j-1] += dp[i][j] * 0.5;
		}
	}
	ld ans=  0;
	for(int i = 1;i <=n;++i)
	{
		ans += 2 * i * dp[0][i];
	}
	cout<<fixed<<setprecision(20)<< ans/2;
	return 0;
}