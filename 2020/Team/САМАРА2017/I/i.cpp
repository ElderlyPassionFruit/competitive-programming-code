#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
const int MOD = 1000000000+7;
int mul(int x, int y)
{
	return (1ll * x* y) % MOD;
}
void add(int &x, int y)
{
	x+=y;
	if( x>MOD) x-=MOD;
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin>>n;
	vector<vector<int>> a(n, vector<int> (n));
	vector<vector<int>> b(n, vector<int> (n));
	vector<vector<int>> c(n, vector<int> (n));
	for(int i = 0; i< n;++i)
	{
		for(int j =0; j< n;++j)
		{
			cin>>a[i][j];
		}
	}
	for(int i = 0; i<n;++i)
	{
		for(int j = 0; j< n;++j)
		{
			cin>>b[i][j];
		}
	}
	for(int i = 0; i< n;++i)
	{
		for(int j = 0; j< n;++j)
		{
			cin>>c[i][j];
		}
	}
	mt19937 rnd(228 + 'i' + 'q' + rand() + time(0));
	vector<vector<bool>> used(n, vector<bool> (n));
	for(int iter = 0;iter< 500000;++iter)
	{
		int x,y;
//		do{
			x = rnd() % n;
			y = rnd() % n;
//		}while(used[x][y]);
		int now = 0;
		for(int k = 0; k< n;++k)
		{
			add(now, mul(a[x][k], b[k][y]));
		}
		if(now!=c[x][y])
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES";
	return 0;
}