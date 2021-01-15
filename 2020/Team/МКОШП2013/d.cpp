#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin>>n;
	vector<pair<int,int>> ans;
	multiset<int> s;
	for(int i =0 ; i< n;++i)
	{
		int x;
		cin>>x;
		s.insert(x);
	}
	while(s.size())
	{
		int x = *s.begin();
		s.erase(s.begin());
		int tx = x;
		int ty = x;
		while(s.find(x+1)!=s.end())
		{
			ty= x+1;
			x++;
			s.erase(s.find(x));
		}
		ans.push_back(make_pair(tx,ty));
	}
	cout<<ans.size()<<endl;
	for(auto i : ans)
	{
		cout<<i.first<<' '<< i.second<<endl;
	}
	return 0;
}