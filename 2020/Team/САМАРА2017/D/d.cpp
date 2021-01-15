#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n,x;
	cin>>n>>x;
	vector<int> a(n);
	for(int i = 0; i < n;++i) cin>>a[i];
		int g = 0;
	for(int i: a)
	{
		g = __gcd(g,i);
	}
	if(x % g)
	{
		cout<<"NO";
	}
	else
	{
		cout<<"YES";
	}
	return 0;
}