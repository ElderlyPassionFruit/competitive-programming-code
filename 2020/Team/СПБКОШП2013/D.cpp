#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,k,t;
	cin>>n>>k>>t;
	vector<int> z(n);
	for(int i= 0; i < n;++i)
	{
		cin>>z[i];
	}
	vector<int> s(n);
	for(int i =0 ; i < n;++i)
	{
		cin>>s[i];
	}
	int tt = 0;
	for(int i  = 0 ; i < n;++i)
	{
		tt += z[i];
		if( tt + k < s[i])
		{
			tt += k;
			//cout<<i<<' ';
			continue;
		}
		if(s[i] < tt) tt += t;
		else tt = s[i] + t;
	}
	cout<<tt;
	return 0;
}