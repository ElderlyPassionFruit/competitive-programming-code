#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("birthday.in", "r", stdin);
	freopen("birthday.out", "w", stdout);
	int n;
	cin >> n;
	vector<pair<int,int>> ok;
	vector<int> cntd(32);
	vector<int> cntm(13);
	vector<vector<int>> adj(32);
	for(int i = 0 ; i < n;++i)
	{
		int a,b;
		cin>>a>>b;
		ok.push_back({a,b});
		adj[a].push_back(b);
		cntd[a] ++;
		cntm[b] ++;
	}
	vector<pair<int,int>> ok1;
	for(int i = 0; i< n;++i)
	{
		int a = ok[i].first;
		if( cntd[a] >= 2)
		{
			bool f =1;
			for(int j : adj[a])
			{
				if(cntm[j] <2)
				{
					f= 0;
					break;
				}
			}
			if(f)
			{
				ok1.push_back(ok[i]);
			}
		}
	}
	cntd.assign(32,0);
	cntm.assign(13,0);
	for(int i  =0 ; i< ok1.size();++i)
	{
		cntm[ok1[i].second] ++;
	}
	vector<pair<int,int>> ok2;
	for(int i = 0; i < ok1.size();++i)
	{
		if(cntm[ok1[i].second ] == 1) ok2.push_back(ok1[i]);
	}
	vector<pair<int,int>> ok3;
	for(int i = 0; i < ok2.size();++i)
	{
		cntd[ok2[i].first]++;
	}
	for(int i  =0 ; i < ok2.size();++i)
	{
		if(cntd[ok2[i].first] == 1) ok3.push_back(ok2[i]);
	}
	cout<<ok3[0].first<<' '<< ok3[0].second;
	return 0;
}