#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,k;
	cin>>n>>k;
	vector<vector<bool>> dp(k + 1, vector<bool> (3 * n + 32));
	dp[0][2*n] = 1;
	for(int j = 0 ; j< k;++j)
	{
		for(int i = 0;i <= 2*n;++i)
		{
			if( dp[j][i])
			{
				if(i > 0)
				dp[j + 1][i - 1] = 1;
				if( i % 2==0)
				{
					dp[j + 1][i/2] = 1;
				}
			}

		}
	}
//	cout<<'j'<<endl;
	vector<int> ans;
	for(int i=0;i <=2*n;++i)
	{
		if( dp[k][i])
		{
			ans.push_back(i);
		}
	}
	cout<<ans.size()<<endl;
	for(int j : ans)
	{
		if( j % 2)
		{
			cout<<j/2<<'.'<< 5<<' ';
		}
		else
		{
			cout<<j/2<<'.'<<0<<' ';
		}
	}
	return 0;
}