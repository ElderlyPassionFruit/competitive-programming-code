#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin>>s;
	string kek = "happiness";
	set<int> pos;
//	cout<<s<<endl;
	//cout<<7;
	for(int i =0; i + kek.size() -1 <s.size();++i)
	{
		bool f = 1;
		for(int j = 0;j < kek.size();++j)
		{
			if(kek[j] != s[i+j])
			{
//				cout<<"j "<< j<<endl;
				f= 0 ;
				break;
			}
		}	
		if(f) pos.insert(i);	
	}
//	for(int i : pos)
//	{
//		cout<<i  <<' ';
//	}
	if(!pos.size())
	{
		//cout<<7;
		map<char, vector<int>> pos;
		for(int  i = 0; i< s.size();++i)
		{
			pos[s[i]].push_back(i);
		}
		cout<<"YES"<<endl;
		for(auto i:pos)
		{
			if(i.second.size() > 1)
			{
				cout<<i.second[0] + 1<<' '<< i.second[1] + 1;
				return 0;
			}
		}
		cout<<1 <<' ' << 2;
		return 0;
	}
	if( pos.size() >2)
	{
		cout<<"NO";
		return 0;
	}
	if( pos.size() ==1)
	{
		cout<<"YES"<<endl;
		cout<<(*pos.begin() )+ 1<< ' ' << (*pos.begin()) + 2<<endl;
	}
	if(pos.size() == 2)
	{
		cout<<"YES"<<endl;
		cout<<(*pos.begin()) +1<<' '<< (*pos.rbegin() +2);
		return 0;
	}
	return 0;
}