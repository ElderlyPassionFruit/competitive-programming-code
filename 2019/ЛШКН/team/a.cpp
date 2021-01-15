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
const int MAXN = 4e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

int n, I;
vector<int> a;

void read() {
	cin >> n >> I;
	I *= 8;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
}

int logs[MAXN];

int cnt(int x) {
	int ans = 0;
	int i = 1;
	while (i < x) {
		ans++;
		i *= 2;
	}
	return ans;
}

void build() {
	logs[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		logs[i] = cnt(i);
	}
	/*cout << "logs = " << endl;
	for (int i = 0; i < 10; i++)
		cout << logs[i] << " ";
	cout << endl;*/
}

map <int, int> have;
int cnt_ans;

void add(int x) {
	if (have[x] == 0)
		cnt_ans++;
	have[x]++;
}

void del(int x) {
	if (have[x] == 1)
		cnt_ans--;
	have[x]--;
}

int get_ans() {
	return cnt_ans;
} 

int ans;

void run() {
	build();
	ans = 1e9 + 10;
	int pos = -1;
	cnt_ans = 0;
	for (int i = 0; i < n; i++) {
		while (pos < n - 1) {
			add(a[pos + 1]);
			if (logs[get_ans()] * n > I) {
				del(a[pos + 1]);
				break;
			}
			pos++;
		}
		//cout << "i = " << i << " pos = " << pos << endl;
		chkmin(ans, n - (pos - i + 1));
		del(a[i]);
	}
}

void write() {
	cout << ans << endl;
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