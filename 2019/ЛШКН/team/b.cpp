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

int n;
int a[MAXN];
int pref[MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
}

void build() {
	for (int i = 1; i <= n; i++)
		pref[i] = pref[i - 1] + a[i];
}

int get(int l, int r) {
	if (r < l)
		return 0;
	return pref[r] - pref[l - 1];
}

int get(int x, int l, int r, int k) {
	return min(get(l, x - 1), get(x + k, r));
}

int get_ans(int l, int r, int k) {
	int l1 = l;
	int r1 = r - k + 1;
	while (l1 < r1 - 2) {
		int mid1 = l1 + (r1 - l1) / 3;
		int mid2 = r1 - (r1 - l1) / 3;
		if (get(mid1, l, r, k) < get(mid2, l, r, k))
			l1 = mid1;
		else
			r1 = mid2;
	}	
	int ans = 0;
	for (int i = l1; i <= min(r - k, l1 + 3); i++) {
		ans = max(ans, get(i, l, r, k));
	}

	return ans;
}

vector<int> ans;

void run() {
	build();
	int q;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int l, r, k;
		cin >> l >> r >> k;
		ans.push_back(get_ans(l, r, k));
	}
}

void write() {
	for (auto i : ans)
		cout << i << "\n";
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