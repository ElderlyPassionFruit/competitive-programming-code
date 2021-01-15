#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll

int binpow(int a,int b)
{
	int res =1;
	while(b)
	{
		if(b&1) res*=a;
		a*=a;
		b>>=1;
	}
	return res;
}

void solve() {
	int n,f,k;
	cin>>n>>f>>k;
	if(n > 40)
	{
		cout<<"YES"<<endl;
		return ;
	}
	int kekos = (f+1) * binpow(2, n - 1) +1;
	if(kekos >= k)
	{
		cout<<"YES"<<endl;
	}
	else
	{
		cout<<"NO"<<endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}