#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("prizes.in","r",stdin);
	freopen("prizes.out","w",stdout);
	int n,m;
	cin>>n>>m;
	if(n > m)swap(n,m);
	if(n==1)
	{
		int x = (m>=3);
		m-=2;
		cout<<x + (m -1) /4;
		return 0;
	}
	if(min(n,m)<=2)
	{
		cout<<0;
		return 0;
	}
	cout<<1;
	return 0;
}