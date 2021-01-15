#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 101;
vector<vector<int>> pref(MAXN, vector<int> (MAXN));
vector<vector<int>> a(MAXN, vector<int> (MAXN));
int get(int x1, int y1, int x2, int y2)
{
	return pref[x2][y2] -pref[x1-1][y2]  -pref[x2][y1-1] + pref[x1-1][y1-1];
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i = 0; i< k;++i)
	{
		int x,y;
		cin>>x>>y;
		a[x][y] =1;
	}
	for(int i = 1;i <=n;++i)
	{
		for(int j = 1; j<=m;++j)
		{
			pref[i][j] = pref[i-1][j] +pref[i][j-1] -pref[i-1][j-1] + a[i][j];
			//cout<<pref[i][j] <<' ';
		}
		//cout<<endl;
	}
	int ans = 0;
	for(int  i1= 1;i1<=n;++i1)
	{
		for(int j1= 1;j1<=m;++j1)
		{
			for(int i2 =i1; i2<=n;++i2)
			{
				for(int j2 = j1; j2<=m;++j2)
				{
					if(get(i1,j1,i2,j2) == get(1,1,n,m))ans++;
				}
			}
		}
	}
	cout<<ans - 1;
	return 0;
}