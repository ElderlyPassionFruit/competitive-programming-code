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

struct segment_tree{
	vector<pair <int, int> > tree;
	int n;

	segment_tree() {
		n = 0;
		tree = {};
	}

	void build(int v, int tl, int tr, vector<pair <int, int> > & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	segment_tree(vector<pair <int, int> > a) {
		n = a.size();
		tree.assign(n * 4, {-INF, -INF});
		build(1, 0, n, a);
	}

	pair <int, int> get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return {-INF, -INF};
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	pair <int, int> get(int l, int r) {
		return get(1, 0, n, l, r + 1);
		//pair <int, int> ans = {-INF, -INF};
		//for (int i = max(l, 0LL); i <= min(r, n - 1); i++)
		//	chkmax(ans, tree[i]);	
		//cout << "l = " << l << " r = " << r << endl;
		//return ans;
	}
};

struct event{
	int a, h, ind;
};
vector<event> a;
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		event x;
		cin >> x.a >> x.h;
		x.ind = i;
		a.push_back(x);
	}
}	

int ans1;
pair <int, int> ans2;

void run() {
	sort(a.begin(), a.end(), [&] (event i, event j) {return i.h < j.h;});
	ans1 = 0;
	ans2 = {0, 1};

	vector<pair <int, int> > b;
	for (auto i : a) {
		b.push_back({i.a, i.ind});
	}
	segment_tree tree(b);

	/*cout << "a = " << endl;
	for (auto i : a)
		cout << i.a << " " << i.h << " " << i.ind << endl; 

	cout << "tree = " << endl;
	for (auto i : tree.tree)
		cout << i.first << " " << i.second << endl;*/

	for (int i = 0; i < n; i++) {
		event x;
		x.h = a[i].a;
		int pos = --upper_bound(a.begin(), a.end(), x, [&] (event i, event j) {return i.h < j.h;}) - a.begin();
		//cout << "i = " << i << " pos = " << pos << endl;
		
		pair <int, int> fans = {-INF, -INF};
		if (pos < i)
			chkmax(fans, tree.get(0, pos));
		else
			chkmax(fans, max(tree.get(0, i - 1), tree.get(i + 1, pos)));

		//cout << "fans = " << fans.first << " " << fans.second << endl;
		
		int fans2 = fans.first + (fans.first >= a[i].h) * a[i].a;

		if (fans2 > ans1) {
			ans1 = fans2;
			ans2 = {a[i].ind, fans.second};
		} 
	}
}

void write() {
	cout << ans1 << endl;
	cout << ans2.first + 1 << " " << ans2.second + 1 << endl;
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