#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 30, MAXM = 15;
int dp[MAXN][1 << MAXM];
int n, m;
void read()
{
	//	cin >> n >> m;
}

bool crr(int a, int b)
{
	for (int i = 1; i < m; i++)
	{
		int cnt = ((a >> i) & 1) + ((a >> (i - 1)) & 1) + ((b >> i) & 1) + ((b >> (i - 1)) & 1);
		if (cnt == 4 || cnt == 0)
			return false;
 	}
 	return true;	
}

void run()
{
	for (int m = 1; m < 4; m++)
	{
		for (int j = 0; j < (1 << m); j++)
		{
		
			int cnt = 0;
			for (int k = 0; k < (1 << m); k++)
			{
				if (crr(j, k))
				{				
				//	dp[i][j] += dp[i - 1][k];
					cnt++;
				}
			}
			cout << m << " " << " " << j << " " << cnt << endl;
		}
	} 
}
void write()
{

}

signed main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen("nice.in", "r", stdin);
	//freopen("nice.out", "w", stdout);

	read();
	run();
	write();
	return 0;
}