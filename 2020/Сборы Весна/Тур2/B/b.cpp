#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}


const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 5e5 + 10;

int par[MAXN];

void make() {
	for (int i = 0; i < MAXN; i++)
		par[i] = i;
}

int get_par(int v) {
	if (v == par[v]) return v;
	return par[v] = get_par(par[v]);
}

int uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return 0;
	par[b] = a;
	return 1;
}

int pows[MAXN];

void build() {
	make();
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++)
		pows[i] = mul(pows[i - 1], 2);
}

int n, m, k;
map<ll, vector<pair<int, int>>> have;
ll c[MAXN];
void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
		cin >> c[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		have[c[u] ^ c[v]].push_back({u, v}); 
	}
}

int ans;

void run() {
	for (auto i : have) {
		int fans = n;
		for (auto j : i.second) {
			fans -= uni(j.first, j.second);
		}
		ans = add(ans, pows[fans]);
		for (auto j : i.second) {
			par[j.first] = j.first;
			par[j.second] = j.second;
		}
	}
	ans = add(ans, mul(sub(pows[k], have.size()), pows[n]));
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	build();
	read();
	run();
	write();
	return 0;
}