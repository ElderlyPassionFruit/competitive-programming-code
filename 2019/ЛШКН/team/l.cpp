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
#define endl '\n'
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
const int MAXN = 3e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double
int l,r;
vector<int> getd(int n)
{
	vector<int> ans;
	for(int i =1;i *i<=n;++i)
	{
		if(n % i == 0)
		{
			if(i >= l && i<=r)
			ans.pbc(i);
			if(i*i !=n ) if(n/  i >=l && n / i<=r)ans.pbc(n / i);
		}
	}
	return ans;
}
int cl[MAXN];
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>l>>r;
	vector<vector<int>> dvvs(3e5+1);
	for(int i= 1;i< dvvs.size();++i)
	{
		dvvs[i] = getd(i);
	}
	cl[l] = 1;
	for(int i = l+1;i<=r;++i)
	{
		auto divs = dvvs[i];
		vector<int> cololo(200);
		for(int j : divs) cololo[cl[j]] = 1;
		for(int cal = 1; cal < 200; ++cal)
		{
			if(cololo[cal] == 0)
			{
				cl[i] = cal;
				break;
			}
		}
	}

	

	set<int> cls;
	for(int i = l;i <=r;++i)
	{
		cls.insert(cl[i]);
	}
	cout<<cls.size()<<endl;
	for(int i =l; i<=r;++i)
	{
		cout<<cl[i]<<' ';
	}
	return 0;
}