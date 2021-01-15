#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 30, MAXM = 15;
int dp[MAXN][1 << MAXM];
int n, m;
void read()
{
	cin >> n >> m;
}

bool crr(int a, int b)
{
	for (int i = 1; i < m; i++)
	{
		int cnt = ((a >> i) & 1) + ((a >> (i - 1)) & 1) + ((b >> i) & 1) + ((b >> (i - 1)) & 1);
	//	cout << i << " " << a << " " << b << " " << cnt << endl;
		if (cnt == 4 || cnt == 0)
			return false;
 	}
 	return true;	
}

void run()
{
	if (n < m)
		swap(n, m);
	for (int j = 0; j < (1 << m); j++)
	{
		dp[0][j] = 1;
	}
	//cout << n << " " << m << endl;
	for (int i = 1; i < n; i++)
	{
	//	cout << i << endl;
		int cnt = 0;
			
		for (int j = 0; j < (1 << m); j++)
		{
			for (int k = 0; k < (1 << m); k++)
			{
				if (crr(j, k))
				{				
					dp[i][j] += dp[i - 1][k];
					cnt += dp[i - 1][k];
				}
			}
		}
		
		cout << i << " " << cnt << endl;	
	}
}

void write()
{
	int ans = 0;
	for (int i = 0; i < (1 << m); i++)
	{
		ans += dp[n - 1][i];
		cout << dp[n - 1][i] << " ";
	}
	cout << endl;
	cout << ans << endl;
//	cout << crr(3, 3) << endl;
}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen("nice.in", "r", stdin);
	//freopen("nice.out", "w", stdout);

	read();
/*	if (n == 2 && m == 3 || n == 3 && m == 2)
	{
		cout << 50 << endl;
		return 0;
	}
*/	run();
/*	for (int i = 1; i <= 30; i++)
	{
		for (int j = 1; j * i <= 30; j++)
		{
			n = i;
			m = j;
			run();

			int ans = 0;
			for (int i = 0; i < 1 << m; i++)
			{
				ans += dp[n - 1][i];
			}

			if (ans == 57)
			{
				cout << n << " " << m << endl;
				return 0;
			}			
			for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < 1 << MAXM; j++)
			dp[i][j] = 0;	
		}
	}
*/	write();
	return 0;
}