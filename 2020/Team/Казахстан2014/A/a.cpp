#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int  x,y;
	cin>>x>>y;
	if(y==0 &&x >=0)
	{
		cout<<0;
		return 0;
	}
	if(x>0 && y !=0)
	{
		cout<<1;
		return 0;
	}
	if(x==0 && y!=0)
	{
		cout<<2;
		return 0;
	}
	if(x < 0 && y!=0)
	{
			cout<<2;
			return 0;
	}
	cout<<3;
	return 0;
}