#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
const int MAXN = 1e5+228;
vector<vector<int>> g(MAXN);
vector<bool> used(MAXN);
int c1 =0, c2 = 0;
const int MOD =(int)1e9 + 7;
void dfs(int v)
{
	used[v] = 1;
	c1++;
	for(int i:g[v])
	{
		c2++;
		if(!used[i]) dfs(i);
	}
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,m;
	cin>>n>> m;
	for(int i= 0 ; i< m;++i)
	{
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	ll ans = 1;
	for(int i=1;i <=n;++i)
	{
		if(!used[i])
		{
			dfs(i);
			if(c1==c2/2)
			{
				ans *= c2/2;
				ans%=MOD;
			}
			c1=c2=0;
		}
	}
	cout<<ans;
	return 0;
}