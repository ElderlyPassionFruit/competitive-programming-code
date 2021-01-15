#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define int ll
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct edge{
	int to, cost, type;
};

const int MAXN = 1e6 + 10;
vector<edge> g[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int s;
		cin >> s;
		int from;
		cin >> from;
		from--;
		for (int j = 0; j < s; j++) {
			int to, cost;
			cin >> cost >> to;
			to--;
			g[from].push_back({to, cost, i});
			from = to;
		}
	}
}

struct event{
	int v, cost;
	event() {}
	event(int a, int b) {
		cost = a, v = b;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.cost, a.v) < tie(b.cost, b.v);
}

const int INF = 1e18 + 10;
int ans_len;
ll ans;
int d[MAXN];

void build_graph() {
	for (int i = 0; i < n; i++)
		d[i] = INF;
	d[0] = 0;
	set<event> q;
	q.insert({0, 0});
	while (!q.empty()) {
		int v = (*q.begin()).v;
		q.erase(q.begin());
		if (v == n - 1) continue;
		for (auto i : g[v]) {
			if (d[i.to] <= d[v] + i.cost) continue;
			q.erase({d[i.to], i.to});
			d[i.to] = d[v] + i.cost;
			q.insert({d[i.to], i.to});
		}
	}

	ans_len = d[n - 1];
	assert(ans_len != INF);
	for (int i = 0; i < n; i++) {
		vector<edge> st;
		for (auto j : g[i]) {
			if (d[j.to] != d[i] + j.cost) continue;
			st.push_back(j);
		}
		g[i] = st;
	}
	g[n - 1].clear();
}

vector<int> order;
bool used[MAXN];

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i.to]) continue;
		dfs(i.to);
	}
	order.push_back(v);
}

void build_order() {
	dfs(0);
}

void build() {
	build_graph();
	build_order();
}

ll sq(ll x) {
	return x * x;
}

struct line{
	ll k, b;
	line() {
		k = 0, b = INF;
	}
	line(ll x, ll y) {
		k = x, b = y;
	}
};

ll eval(line l, ll x) {
	return l.k * x + l.b;
}

ld cross(line l, line m) {
	return ((ld)l.b - m.b) / (m.k - l.k);
}

struct cht{
	vector<line> l;
	vector<ld> p;
	cht() {}

	void add(line x) {
		while (!p.empty() && p.back() <= cross(x, l.back()))
			p.pop_back(), l.pop_back();
		l.push_back(x);
		if (l.size() >= 2)
			p.push_back(cross(l.back(), l[l.size() - 2]));
	}

	ll get(ll x) {
		ll ans = -INF;
		for (auto i : l)
			chkmax(ans, eval(i, x));
		return ans;
	}
};

ll dp[MAXN];
map<int, cht> have[MAXN];

void calc() {
	for (auto v : order) {
		dp[v] = -INF;
		if (v == n - 1) {
			dp[v] = 0;
		}
		for (auto i : g[v]) {
			swap(have[v][i.type], have[i.to][i.type]);
			if (dp[i.to] != -INF && d[i.to] != INF) {
				have[v][i.type].add(line(2LL * d[i.to], sq(d[i.to]) + dp[i.to]));
			}
			ll fans = have[v][i.type].get(-d[v]);
			if (fans != -INF)
				chkmax(dp[v], fans + sq(d[v]));
			//have[v][i.type].push_back(i.to);
			//for (auto j : have[v][i.type]) {
			//	chkmax(dp[v], dp[j] + sq(d[j] - d[v]));
			//}
		}
	}
	ans = dp[0];
}

void run() {
	build();
	calc();
}

void write() {
	cout << ans_len << " " << ans << endl;
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