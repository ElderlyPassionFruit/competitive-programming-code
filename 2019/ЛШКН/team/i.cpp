//#pragma GCC optimize("SEX_ON_THE_BEACH")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,popcnt,tune=native")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rev(x) reverse(all(x))
#define pbc push_back
#define pob pop_back()
#define mx(x) *max_element(all(x))
#define mn(x) *min_element(all(x))
#define rall(x) x.rbegin(), x.rend()
#define vin(v) for(auto &i : v) cin >> i;
#define vout(v, c) for (auto &i : v) cout << i << c;
#define endl '\n'
#define gcd(a, b) __gcd(a, b)
#define pop_cnt(a) __builtin_popcount(a)

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template<typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(NULL));

const int inf = 1e9 + 10;
const ll INF = 1e18 + 10;
const int MAXN = 1e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

vector<vector<int>> pref;
int n;
int get(int x1, int y1, int x2, int y2)
{
	return pref[x2][y2] - pref[x1-1][y2] - pref[x2][y1-1] + pref[x1-1][y1-1];
}
int getd(vector<vector<char>> kek)
{
	vector<vector<int>> dp(n+1, vector<int> (n+1,n));
	
	for(int i= 0; i <=n;++i)
	{
		dp[0][i] =  dp[i][0] = 0;
	}
	pref= dp;
	for(int i=1;i <=n;++i)
	{
		for(int j =1;j <=n;++j)
		{
			pref[i][j] =pref[i][j-1] + pref[i-1][j] - pref[i-1][j-1] + (kek[i][j] == '#');
		//	cout<<pref[i][j]<<' ';
		}
		//cout<<endl;
	}
	for(int i = 1;i <=n;++i)
	{
		for(int j = 1;j<=n;++j)
		{
			int cnt = 0;
			for(int x1=  1;x1 <= i; ++x1)
			{
				for(int y1 = 1; y1<=j;++y1)
				{
					cnt += (kek[x1][y1] == '#');
				}
			}
			if(!cnt)
			{
				dp[i][j] = 0;
				continue;
			}
			for(int len1 =1; len1 <= i ;++len1)
			{
				for(int len2 = 1;len2<= j;++len2)
				{
					int cnt = get(i - len1 + 1, j - len2 + 1, i, j);
					dp[i][j] = min(dp[i][j], dp[i - len1][j]  + dp[i][j-len2] - dp[i-len1][j-len2] + (cnt > 0 ? 1 : 0) * max(len1,len2));
				}
			}
		}
	}
	return dp[n][n];
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	vector<vector<char>> kek(n+1, vector<char> (n+1));
	for(int i = 1;i <=n;++i)
	{
		for(int j = 1;j <=n;++j)
		{
			cin>>kek[i][j];
			//cout<<kek[i][j];
		}
	//	cout<<endl;
	}

	int ans = getd(kek);
	//cout << ans << endl;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			rev(kek);
			chkmin(ans, getd(kek));
		}
		for(int  j =  0 ; j<=n;++j)
		{
			reverse(kek[j].begin() + 1, kek[j].end());
		}
	}
	cout<<ans;
	return 0;
}