#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

ll calc(ll l)
{
	if(!l)return 0;
	vector<vector<vector<ll>>> dp(20, vector<vector<ll>> (10, vector<ll> (3)));
	string s = to_string(l);
	for(int i  = 1;i <= 9;++i)
	{
		dp[1][i][ (i == s[0] - '0' ? 1 : ( i <s[0] - '0' ? 0 : 2))]++;
	}
	for(int len = 1; len <s.size();++len)
	{
		for(int mx =0 ;mx < 10;++mx)
		{
			for(int dig= 0 ;dig < 10;++dig)
			{
				for(int fl =0 ;fl<3;++fl)
				{	
				 	int tmx = max(mx, dig);
					int tlen = len+1;
					int tfl;
					if(!fl) tfl= 0 ;
					else if(fl==2) tfl=2;
					else
					{
						if( dig == s[len]- '0') tfl=1;
						else if( dig < s[len] - '0') tfl = 0;
						else tfl= 2;
					}
					dp[tlen][tmx][tfl] += dp[len][mx][fl];
				}
			}
		}
	}
	ll ans= 0;
	for(int len=1;len<=s.size();++len)
	{
		for(int mx =0; mx < 10;++mx)
		{
			if(len<s.size()) ans += 1ll *mx * (dp[len][mx][0] + dp[len][mx][1] + dp[len][mx][2]);
			else ans += 1ll * mx * (dp[len][mx][0] + dp[len][mx][1]);
		}
	}
	return ans % MOD;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll l,r;
	cin>>l>>r;
	cout<< (calc(r) - calc(l-1) + MOD) % MOD;
	return 0;
}