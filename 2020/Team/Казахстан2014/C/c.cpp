#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
ll gcd(ll a, ll b)
{
	while(b)
	{
		a%=b;
		swap(a,b);
	}
	return a;
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	ll s,b,c,d;
	cin>>s>>b>>c>>d;
	ll n =abs(s-c);
	ll m = abs(b-d);
	cout<< n+m+2-  gcd(n+1, m+1);
	return 0;
}