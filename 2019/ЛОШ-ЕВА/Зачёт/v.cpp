#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
ll p;

vector<ll> merge(vector<ll> & a, vector<ll> & b, ll x) {
	if (a.empty()) {
		vector<ll> ans = b;
		for (auto &i : ans)
			i += x;
		return ans;
	}
	if (b.empty()) return a;
	vector<ll> ans;
	int pos1 = 0, pos2 = 0;
	while (pos1 < a.size() && pos2 < b.size()) {
		if (a[pos1] <= b[pos2] + x) {
			while (ans.size() >= 2 && ans[ans.size() - 2] * p >= a[pos1] * (p - 1))
				ans.pop_back();
			ans.push_back(a[pos1]);
			pos1++;
		}
		else {
			while (ans.size() >= 2 && ans[ans.size() - 2] * p >= (b[pos2] + x) * (p - 1))
				ans.pop_back();
			ans.push_back(b[pos2] + x);
			pos2++;
		}
	}

	while (pos1 < a.size()) {
		while (ans.size() >= 2 && ans[ans.size() - 2] * p >= a[pos1] * (p - 1))
			ans.pop_back();
		ans.push_back(a[pos1]);
		pos1++;
	}

	while (pos2 < b.size()) {
		while (ans.size() >= 2 && ans[ans.size() - 2] * p >= (b[pos2] + x) * (p - 1))
			ans.pop_back();
		ans.push_back(b[pos2] + x);
		pos2++;
	}
	return ans;		
}

struct ed{
	int v;
	ll cost;
	ed() {}
	ed(int a, ll b) {
		v = a, cost = b;
	}
};

const int MAXN = 5e5 + 10;

int n, m, q;
vector<ed> g[MAXN];
vector<ll> dp[MAXN];

void read() {
	//cin >> n >> m >> q >> p;
	scanf("%d%d%d%lld",&n,&m,&q,&p);
	for (int i = 0; i < m; i++) {
		int v, u;
		ll d;
		//cin >> v >> u >> d;
		scanf("%d%d%lld",&v,&u,&d);
		v--;
		u--;
		g[v].push_back({u, d});
	}
}

void build() {
	dp[0].push_back(0);
	for (int v = 0; v < n; v++)
		for (auto i : g[v])
			dp[i.v] = merge(dp[i.v], dp[v], i.cost);
}

bool check(int f, ll r) {
	int pos = lower_bound(all(dp[f]), r) - dp[f].begin();
	if (pos == dp[f].size()) return false;
	return r <= dp[f][pos] && dp[f][pos] * (p - 1) <= r * p;
}

void run() {
	build();
	for (int i = 0; i < q; i++) {
		int f;
		ll r;
		//cin >> f >> r;
		scanf("%d%lld",&f,&r);
		f--;
		cout << (char)('0' + check(f, r));
		//cout.flush();
	}
}

void write() {
	cout << "\n";
}

void clear() {
	for (int i = 0; i < n; i++)
		g[i].clear(), dp[i].clear();
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		clear();
		read();
		run();
		write();
	}
	return 0;
}