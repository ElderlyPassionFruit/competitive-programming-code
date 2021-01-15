#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int len(int n)
{
	if(!n) return 1;
	int ans= 0 ;
	while(n)
	{
		ans++;
		n/=10;
	}
	return ans;
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	string s,a,b,c;
	cin>>s>>a>>b>>c;
	set<char> kek;
	for(auto i : s) kek.insert(i);
//	cout<<kek.size()<<endl;
	if( kek.size() > 12)
	{
		//assert(0);
		cout<<0;
		return 0;
	}
	vector<string> xx(3);
	int l = 0;
	vector<int> pos(26);
	for(char i:s)
	{
		if(i == '+' ||i == '=')
		{
			l++;
		}
		else
		{
			xx[l] .pb(i);
		}
	}
	a = xx[0], b = xx[1], c = xx[2];
	int cnt= 0;
	vector<char> let;
	for(char i : kek)
	{
		if( i!= '+' && i!='=')
		{
			pos[i -'A'] = cnt;
			let.pb(i);
			cnt++;
		}
	}
	vector<int> perm{0,1,2,3,4,5,6,7,8,9};
	set<vector<int>> ansset;
	do{
		int numa = 0 ;
		for(char i : a)
		{
			numa *=10;
			numa += perm[pos[i - 'A']];
		}

		int numb = 0 ;
		for(char i : b)
		{
			numb *=10;
			numb += perm[pos[i - 'A']];
		}
		int numc = 0 ;
		for(char i : c)
		{
			numc *=10;
			numc += perm[pos[i - 'A']];
		}
		if(numa + numb == numc) ansset.insert({numa, numb, numc});
	}while(next_permutation(all(perm)));
	cout<<ansset.size()<<endl;
	for(auto i : ansset)
	{
		int xa = i[0];
		int d = a.size() - len(xa);
		for(int j = 0; j < d;++j)
		{
			cout<<0;
		}
		cout<<xa <<'+';
		xa = i[1];
		d = b.size() - len(xa);
		for(int j = 0; j < d;++j)
		{
			cout<<0;
		}
		cout<<xa<<'=';
		xa = i[2];
		d = c.size() - len(xa);
		for(int j = 0; j < d;++j)
		{
			cout<<0;
		}
		cout<<xa<<endl;
	}
	return 0;
}