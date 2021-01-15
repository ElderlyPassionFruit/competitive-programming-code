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

struct event{
	int a, b, c;
};

int n;
vector<event> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.a >> i.b >> i.c;
}

vector<int> ans;

void run() {
	vector<int> sums;
	for (int i = 0; i < n; i++) {
		int x = a[i].a + a[i].b + a[i].c - max(a[i].a, max(a[i].b, a[i].c));
		sums.push_back(x);
	}
	sort(sums.begin(), sums.end());
	for (int i = 0; i < n; i++) {
		int sum = a[i].a + a[i].b + a[i].c - 2;
		int pos = (--upper_bound(sums.begin(), sums.end(), sum) - sums.begin()) + 1;
		if (a[i].a + a[i].b + a[i].c - max(a[i].a, max(a[i].b, a[i].c)) <= sum)
			pos--;
		ans.push_back(pos);
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}