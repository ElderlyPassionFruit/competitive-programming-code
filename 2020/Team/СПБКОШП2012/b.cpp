#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("checkpaint.in", "r", stdin);
	freopen("checkpaint.out", "w", stdout);

	int n, m;
	cin>>m>>n;
	vector<bool> a(m + 228);
	for(int i= 0; i< n;++i)
	{
		int l,r;
		cin>>l>>r;
		for(int j = l; j<=r;++j) a[j] =1;
	}
	if(count(all(a), 1) == m)
	{
		cout<<"YES";
	}
	else
	{
		cout<<"NO";
	}
	return 0;
}