#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define pbc push_back
#define all(x)( x).begin(),(x).end()
#define int ll
const int inf = 1e18;

int calc(int n, int k) {
	int kekos = (n - 1) / k ;
	int f1 = kekos * n * n;
	int f2 = kekos * n;
	int f3 = kekos * (kekos + 1) * k * n;
	int f4 = (kekos+1) * kekos * (kekos * 2 + 1) /6 *k * k;
	int f5 = k * kekos * (kekos + 1) / 2;
	return (f1 - f2 - f3 + f4 + f5) / 2;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("traffic.in","r",stdin);
	freopen("traffic.out","w",stdout);
	int n,k;
	cin>>n>>k;
	vector<int> a(n + 1);
	for(int i = 1; i <= n;++i)
		cin>>a[i];
//	keke(a,k);
	vector<vector<int>> dp(n+10, vector<int> (k+10,  inf));
	vector<vector<int>> p(n+10, vector<int> (k+10, inf));
	dp[0][0] = 0;
	for(int i=1;i <=n;++i)
	{
		for(int j = 1;  j<= k;++j)
		{
			for(int kk = 1;kk <=j;++kk)
			{
				int ndp = dp[i-1][j -kk] + calc(a[i], kk);
				if(ndp < dp[i][j])
				{
					dp[i][j] = ndp;
					p[i][j] = kk;
				}
			}
		}
	}
	cout<<dp[n][k] << endl;
	vector<int> ans;
	int ti = n;
	int tk = k;
	while(ti )
	{
		 int pp = p[ti][tk];
		 ans.pbc(pp);
		 ti--;
		 tk-=pp;
	}
	reverse(all(ans));
	for(int i : ans)
	{
		cout<<i<<' ';
	}
	return 0;
}