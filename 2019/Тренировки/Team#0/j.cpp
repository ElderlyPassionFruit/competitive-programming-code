#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n;
	cin>>n;	
	vector<int> a(n);
	multiset<int> s;
	for(int &i : a) cin>>i;
	for(int i: a) s.insert(i);
	int ans = 0;	
	while(s.size() > 1)
	{
		if(s.size() == 2)
		{
			cout<<ans+1;
			return 0;
		}
		int mn = *s.begin();
		s.erase(s.begin());
		int tx = *s.rbegin();
		s.erase(s.find( *s.rbegin()));
		int ty=  *s.rbegin();
		s.erase(s.find(*s.rbegin()));
		mn--;
		tx+=1+ty;
		s.insert(tx);
		if(mn) s.insert(mn);
		ans++;
	}
	cout<<ans;
	return 0;
}