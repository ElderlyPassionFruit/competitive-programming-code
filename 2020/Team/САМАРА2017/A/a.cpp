#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin>>n;
	vector<pair<int,int >> a(n);
	int toc = 0;
	for(int i = 0; i< n;++i)
	{
		a[i].second = i;
		string s;
		cin>>s;
		int cnt=  0;
		for(int j  = 0 ; j< s.size();++j)
		{
			if(s[j] == ')')  cnt--;
			else cnt++;
		}
		toc += cnt;
		a[i].first =cnt;
	}
	sort(all(a));
	reverse(all(a));
	if( toc!=0)
	{
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	for(auto i :a)
	{
		cout<<i.second + 1 <<' ' ;
	}
	return 0;
}