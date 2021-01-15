#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 110;
int n;
long double arr[MAXN];
long double dp[MAXN][MAXN];

void read()
{
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> arr[i];
	}	
}

void run()
{
	for (int i = 1; i <= n; i++)
		dp[i][i] = arr[i];

	for (int i = 2; i <= n; i++)
	{
		for (int j = i - 1; j >= 1; j--)
		{
			for (int k = j; k < i; k++)
			{
				dp[j][i] = max(dp[j][i], (dp[j][k] + dp[k + 1][i]) / 2);
			}
		}
	}
/*	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cout << "j = " << j << " " << "i = " << i << " " <<  dp[j][i] << endl;
		}
	}*/
}

void write()
{
	cout.precision(20);
	cout << dp[1][n] << endl;;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}	