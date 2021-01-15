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
const int MAXN = 1e7 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;

#define int long long
#define double long double

void no() {
	cout << "NO\n";
	exit(0);
}

const int MAXK = 1e5 + 10;

vector<int> g[MAXK];
int color[MAXK];

void dfs(int v, int c) {
	color[v] = c;
	for (auto i : g[v]) {
		if (color[i] == c)
			no();
		if (color[i] == 0)
			dfs(i, 3 - c);
	}
}

int lp[MAXN];

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	vector<int> pr;

	for(int i = 2; i < MAXN; i++) {
		if(!lp[i]) {
			lp[i] = i;
			pr.pbc(i);
		}
		for(int j = 0; j < pr.size()&& pr[j] *i < MAXN && pr[j]<=lp[i];++j)
		{
			lp[i*pr[j]] = pr[j];
		}
	}

	//cout << "puhh" << endl;

	map <int, vector<int> > nums;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		while (x > 1) {
			int a = lp[x];
			nums[lp[x]].push_back(i);
			while (x % a == 0)
				x /= a;
		}
	}
	
	//cout << "puhh" << endl;
	for (auto i : nums) {
		if (i.second.size() > 2) {
			no();
		}
		if (i.second.size() == 2) {
			int u = i.second[0];
			int v = i.second[1];
			g[u].push_back(v);
			g[v].push_back(u);
		}
	}

	//cout << "puhh" << endl;
	for (int i = 0; i < n; i++) {
		if (!color[i])
			dfs(i, 1);
	}
	//cout << "puhh" << endl;
	cout << "YES\n";
	for (int i = 0; i < n; i++)
		cout << color[i] << " ";
	cout << "\n";

	return 0;
}