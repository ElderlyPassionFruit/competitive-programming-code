#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
const int MAXN = (int)2e6+1;
bool pr[MAXN];
int prs[MAXN];
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	pr[0]= pr[1] =1;
	for(int i = 2; i < MAXN;++i)
	{
		if( !pr[i])
		{
			for(ll j = i + i ; j< MAXN; j+=i)
			{
				pr[j] = 1;
			}
		}
	}
	for(int i= 2; i< MAXN;++i) prs[i] = prs[i-1] +( pr[i] == 0);
	int q;
	cin>>q;
	while(q--)
	{
		int l,k;
		cin>>l>>k;
		if(k>9800)
		{
			cout<<-1<<endl;
			continue;
		}
		if(k > l /6)
		{
			cout<<-1<<endl;
			continue;
		}
		int nw = l;
		int np = prs[nw];
		bool f =0;
		int i = l;
		for(int kek = l+ 1000; ;kek += 1000)
		{
			if(prs[kek] - prs[kek - l]  >= k) 
			{
				i = kek;
			}
			else break;
		}
		np = prs[i] -  prs[i-l];
		for(int ti = i;ti <  i + 2000;++ti)
		{
			//cout<<ti <<' '<< np<<endl;
			if(np == k)
			{
				cout<<ti-l+1<<' '<<ti<<endl;
				f = 1;
				break;
			}
			np += (pr[ti + 1] == 0);
			np -= (pr[ti - l + 1] == 0);
		}
		if(f)continue;
		cout<<-1<<endl;
	}
	return 0;
}