//#pragma GCC optimize("SEX_ON_THE_BEACH")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,popcnt,tune=native")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
using namespace std;

#define all(x) x.begin(), x.end()
#define rev(x) reverse(all(x))
#define pbc push_back
#define pob pop_back()
#define mx(x) *max_element(all(x))
#define mn(x) *min_element(all(x))
#define rall(x) x.rbegin(), x.rend()
#define vin(v) for(auto &i : v) cin >> i;
#define vout(v, c) for (auto &i : v) cout << i << c;
//#define endl '\n'
#define gcd(a, b) __gcd(a, b)
#define pop_cnt(a) __builtin_popcount(a)

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

template<typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(NULL));
const int inf = 1e9 + 10;
const ll INF = 1e18 + 10;
const int MAXN = 1e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

pair<int,int> cntkek(int n, int msk, int bit)
{
	pair<int,int> ololo;
	for(int i =0 ; i <=n;++i)
	{
		int nw=  0;
		for(int j = 0; j<=bit;++j)
		{
			if(i & ( 1<<j))
			{
				nw |= (1<<j);
			}
		}
		if(nw== msk)
		{
			if((i >>bit) & 1)
			{
				ololo.second++;
			}
			else 
			{
				ololo.first++;
			}
		}
	}
	return ololo;
}

signed main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	vector<int> poses(n);
	iota(all(poses), 0);
	//vout(poses, ' ');
	int bt = 0;
	int nownum = 0;
	while(poses.size())
	{
		vector<int> pos0, pos1;
		for(int i : poses)
		{
			cout<<"? "<< i+1<<' '<< bt<<endl;	
			int x;
			cin>>x;
			if(x) pos1.pbc(i);
			else pos0.pbc(i);
		}
		auto kek = cntkek(n,nownum,bt);
		if( pos0.size() == kek.first)
		{
			poses = pos1;
			nownum |= (1<<bt);
		}
		else
		{
			poses = pos0;
		}
		bt++;
	}
	cout<<"! "<<nownum<<endl;
	return 0;
}