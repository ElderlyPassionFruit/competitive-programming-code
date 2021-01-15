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
	int kl,kr;
	cin>>kl>>kr;
	for(int i=  kl; i<=kr;++i)
	{
		if(i == 1)
		{
			cout<<"FALSE"<<endl;
		}
		else
		{
			cout<<"TRUE"<<endl;
		}
	}
	return 0;
}