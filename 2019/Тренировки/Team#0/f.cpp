#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long double ld;
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int inf  = 1e12 + 20;
const ld EPS = 1e-8;
int n,m,k,p,q;
bool check(int am)
{
	return (ld)k/(n * m) * p * am +EPS >= (ld)q;
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	cin>>n>>m>>k>>p>>q;
	int l = -1, r= inf;
	while(r-l>1)
	{
		int  m= (l+r)/2;
		if(check(m))r = m;
		else l = m;
	}
	if(!check(r)) r--;
	if(check(r+1))r++;
	cout<<r-1;
	return 0;
}