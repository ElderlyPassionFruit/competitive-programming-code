#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm,tune=native")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct plate{
	int a, cost;
	plate() {}
};

struct lunch{
	int cost;
	vector<int> ind;
	lunch() {}
};

int n;
vector<plate> a;
int m;
vector<lunch> b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i.a >> i.cost;
	cin >> m;
	b.resize(m);
	for (auto &i : b) {
		int k;
		cin >> k >> i.cost;
		i.ind.resize(k);
		for (auto &j : i.ind)
			cin >> j;
	}
}

const ll INF = 1e18;
ll ans = INF;

int cnt;

void build() {
	vector<int> have;
	for (auto i : a)
		have.push_back(i.a);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	cnt = have.size();
	for (auto &i : a)
		i.a = lower_bound(all(have), i.a) - have.begin();
	for (auto &i : b) {
		vector<int> nind;
		for (auto j : i.ind) {
			if (binary_search(all(have), j))
				nind.push_back(lower_bound(all(have), j) - have.begin());
		}
		i.ind = nind;
	}
}

const int MAXN = 210;
int used[MAXN];

ll calc(int mask) {
	ll fans = 0;
	for (int i = 0; i < m; i++) {
		if (((mask >> i) & 1) == 0) continue;
		fans += b[i].cost;
	}
	if (fans > ans) return INF;
	for (int i = 0; i < m; i++) {
		if (((mask >> i) & 1) == 0) continue;
		for (auto j : b[i].ind)
			used[j] = mask;
	}
	
	for (auto i : a) {
		if (used[i.a] != mask)
			fans += i.cost;
	}
	return fans;
}

void run() {
	for (int i = 0; i < MAXN; i++)
		used[i] = -1;
	build();
	for (int mask = 0; mask < (1 << m); mask++) {
		chkmin(ans, calc(mask));
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