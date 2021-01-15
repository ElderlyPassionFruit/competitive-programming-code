#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
#define int ll

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin>>n;
	vector<set<int>> kekos(3123);
	vector<vector<int>> wtf(32, vector<int> (32));
	vector<int> cntd(32);
	vector<int> cntm(32);
	for(int i = 0;  i< n;++i)
	{
		int d,m;
		cin>>d>>m;
		cntd[d] ++;
		cntm[m] ++;
		wtf[d][m] ++;
		kekos[d].insert(m);
	}
	for(int i = 1;i <=31;++i)
	{
		if(cntd[i] < 2)continue;
		bool f = 1;
		for(int j : kekos[i])
		{
			if(cntm[j] <2) f = 0;
		}
		if(f)
		{
			cout<<i<<' ';
			for(int j = 1;j<=12;++j)
			{
				if(wtf[i][j] ==1)
				{
					cout<<j;
					return 0;
				}
			}
		}
	}
	return 0;
}