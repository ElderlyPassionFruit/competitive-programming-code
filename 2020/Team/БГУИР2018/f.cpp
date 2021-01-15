#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("SEXONTHEBEACH")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int t;
	cin>>t;
	while(t--)
	{
		map<pair<int,int>, int> d;
		int n,m,k;
		cin>>n>>m>>k;
		if( k % __gcd(n,m) || ( k > n && k> m))
		{
			cout<<-1<<endl;
			continue;
		}
		d[{0,0}] = 0;
		queue<pair<int,int>> q;
		q.push({0,0});
		while(q.size())
		{
			pair<int,int> v = q.front();
		//	cout<<v.first<<' '<< v.second <<' ' << d[{v.first, v.second}]<<endl;
			if( v.first == k|| v.second == k)
			{
				cout<< d[{v.first,v.second}	]<<endl;
				break;
			}
			q.pop();
			if(!d.count({v.first, m}))
			{
				d[{v.first, m}] = d[v]+ 1;
				q.push({v.first, m});
			}
			if(!d.count({n, v.second}))
			{
				d[{n,v.second}] = d[v] + 1;
				q.push({n, v.second});
			}
			if(! d.count({v.first, 0}))
			{
				d[{v.first, 0}] = d[v] + 1;
				q.push({v.first,0});
			}
			if(! d.count({0,v.second}))
			{
				d[{0, v.second}] = d[v]+ 1;
				q.push({0, v.second});
			}
			int x= v.first;
			int y = v.second;
			int posos = min(y, n-x);
			if(!d.count({x + posos, y - posos}))
			{
				d[{x+ posos, y- posos}] = d[v]  + 1;
				q.push({x+posos, y-  posos});
			}
			posos = min(x, m - y);
			if(!d.count({x - posos, y + posos}))
			{
				d[{x - posos, y + posos}] = d[v]+ 1;
				q.push({x-posos, y + posos});
			}

		}

	}
	return 0;
}