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
const int MAXN = 1e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double
const int modfft = 998244353;
ll binpow(ll a, ll b)
{
	ll res= 1;
	while(b)
	{
		if( b & 1)
		{
			res*=a;
			res%=modfft;
		}
		a*=a;
		a%=modfft;
		b>>=1;
	}
	return res;
}
int fc =1;
ll inv(ll a, ll b)
{
	return binpow(a, b - 2);
}
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,t;
	cin>>n>>t;
	if(n > t) 
	{
		cout<<0;
		return 0;
	}
	int cnt = 1;
	int fc2 =1;
	for(int i= t- 2; ;i --)
	{
		cnt++;
		fc = (1ll *fc *i ) % modfft;
		if(cnt>n) break;
	}
	for(int i =1;i <=n- 1;++i)
	{
		fc2=  (1ll *fc2* i) % modfft;
	}
	ll x = inv(t, modfft);
	cout<<x<<endl;
	ll y = binpow(x, n-1);
	cout<< y*fc%modfft;

	return 0;
}