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
const int MAXN = 3e5 + 228;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const int MOD7 = 1e9 + 7;
 
#define int long long
#define double long double
 
vector<int> g[MAXN];
map<pair <int, int>, int> ed;
int n, m;
 
void clear() {
	ed.clear();
	for (int i = 0; i <= 3 * n; i++)
		g[i].clear();
}
 
void read() {
	cin >> n >> m;
//	n = 4;
//	m = rand() % 50;
	//cout << n << " " << m << endl;
	clear();
	//set<pair <int, int> > have;
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		//u--;
		//v--;
		//cout<<"puhh"<<endl;
		//u = rand() % 10;
	//	v = rand() % 10;
	/*	while (u == v || have.count({min(u, v),max(u, v)})) {
			u = rand() % 10;
			v = rand() % 10;
			cnt++;
			if (cnt > 1000)
				break;
		}*/
		//cout << u << " " << v << endl;
		//have.insert({min(u, v), max(u, v)});
		ed[{u, v}] = i;
		ed[{v, u}] = i;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	//cout<<"puhh"<<endl;
}
 
pair <string, vector<int> > ans1, ans2;

void solve1() {
	//cout<<"puhh"<<endl;
	ans1.first = "Matching";
	ans1.second.clear();
	//cout<<"puhh"<<endl;
	for (int i = 0; i < 3 * n; i++) {
		sort(g[i].begin(), g[i].end(), [&] (int a, int b) {return g[a].size() < g[b].size();});
	} 
 	set<pair <int, int> > a;
 	vector<int> dec(3 * n);

 	for (int i = 0; i < 3 * n; i++) {
 		a.insert({g[i].size(), i});
 		dec[i] = g[i].size();
 	}
 	//cout << "puhh" << endl;
	while (!a.empty()) {
		auto x = *(a.begin());
		int v = x.second;
		//cout << "v = " << v << endl;
		a.erase(a.begin());

		for (auto i : g[v]) {
			if (a.find({dec[i], i}) == a.end())
				continue;
			for (auto j : g[i]) {
				if (a.find({dec[j], j}) == a.end())
					continue;
				a.erase({dec[j], j});
				dec[j]--;
				a.insert({dec[j], j});
			}
			a.erase({dec[i], i});
			ans1.second.push_back(ed[{i, v}]);
			break;	
		}
	}
 
	while (ans1.second.size() > n)
		ans1.second.pop_back();
		
	/*if (ans.second.size() != n) {
		cout << "g = " << endl;
		for (int i = 0; i < 3 * n; i++) {
			for (auto j : g[i])
				cout << j << " ";
			cout << endl;
		}
	}
	cout << "ans = " << endl;
	for (auto i : ans.second)
		cout << i << " ";
	cout << endl;*/

	if (ans1.second.size() < n) {
		ans1.first = "Impossible";
		ans1.second.clear();
	}
	//assert(ans.second.size() == n);
}
 
void solve2() {
	ans2.first = "IndSet";
	ans2.second.clear();
	vector<bool> used(3 * n);
 
	vector<int> a(3 * n);
	for (int i = 0; i < 3 * n; i++)
		a[i] = i;
	sort(a.begin(), a.end(), [&] (int i, int j) {return g[i].size() < g[j].size();});
 
	for (auto i : a) {
		if (used[i])
			continue;
		used[i] = true;
		for (auto j : g[i]) {
			used[j] = true;
		}
		ans2.second.push_back(i);
	}
	/*cout << "g = " << endl;
	for (int i = 0; i < 3 * n; i++) {
		for (auto j : g[i])
			cout << j << " ";
		cout << endl;
	}
 
	cout << "ans = " << endl;
	for (auto i : ans.second)
		cout << i << " ";
	cout << endl;
 
	cout << "used = " << endl;
	for (auto i : used)
		cout << i << " ";
	cout << endl;*/
 
	while (ans2.second.size() > n)
		ans2.second.pop_back();

	if (ans2.second.size() < n) {
		ans2.first = "Impossible";
		ans2.second.clear();
	}
//	assert(ans.second.size() == n);
}

pair <string, vector<int>> ans;

void run() {
	solve1();
	solve2();
	if (ans1.first != "Impossible")
		ans = ans1;
	else
		ans = ans2;
}	
 
void write() {
	cout << ans.first << endl;
	if (ans.second.size()) {
		for (auto i : ans.second)
			cout << i + 1 << " ";
		cout << endl;
	}
}
 
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	//int t = 10000;
	while (t--) {
		read();
		run();
		write();
	}
	return 0;
}