#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MAXN = 110;
char str[MAXN];
int dp[MAXN][MAXN];
string ans[MAXN][MAXN];
int n;
void read()
{
	string s;
	cin >> s;
	n = s.length();
	for (int i = 1; i <= n; i++)
	{
		str[i] = s[i - 1];
	}	
}

void run()
{
	for (int i = 0; i < MAXN; i++)
	{
		for (int j = i; j < MAXN; j++)
		{
			dp[i][j] = 1e9;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			if ((str[j] == '[' && str[i] == ']') || (str[j] == '(' && str[i] == ')') || (str[j] == '{' && str[i] == '}'))
			{
				if (dp[j][i] > dp[j + 1][i - 1])
				{
					dp[j][i] = dp[j + 1][i - 1];
					ans[j][i] = str[j] + ans[j + 1][i - 1] + str[i];
				}
			}
			if (j == i)
				dp[j][i] = 1;

			for (int k = j; k <= i; k++)
			{
				if (dp[j][i] > dp[j][k] + dp[k + 1][i])
				{
					dp[j][i] = dp[j][k] + dp[k + 1][i];
					ans[j][i] = ans[j][k] + ans[k + 1][i];
				}
			}
			//cout << "i = " << i << " " << "j = " << j << " " << dp[j][i] << endl;
		}
	}
}

void write()
{
	//cout << dp[1][n] << endl;
	cout << ans[1][n] << endl;
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