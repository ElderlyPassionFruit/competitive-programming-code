#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
//#define int ll
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int v1, u1, v2, u2, w;
};

const int MAXN = 810;

namespace matroid_intersection{
	// Кто это читает тот ЗЗЗДОХНЕТ
	int n, m;
	bool S[MAXN];
	bool g[MAXN][MAXN];
	vector<event> have;
	bool y1[MAXN], y2[MAXN];
	int p[MAXN], sz[MAXN];
	ll ans = 0;

	void make() {
		for (int i = 0; i < n; i++)
			p[i] = i, sz[i] = 1;
	}

	int get_p(int v) {
		if (v == p[v]) return v;
		return p[v] = get_p(p[v]);
	}

	void uni(int u, int v) {
		u = get_p(u);
		v = get_p(v);
		if (u == v) return;
		if (sz[u] < sz[v]) swap(v, u);
		sz[u] += sz[v];
		p[v] = u;
	}

	void build_graph() {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				g[i][j] = false;

		for (int i = 0; i < m; i++) {
			if (!S[i]) continue;
			make();
			for (int j = 0; j < m; j++) {
				if (i == j) continue;
				if (!S[j]) continue;
				uni(have[j].v1, have[j].u1);
			}
			for (int j = 0; j < m; j++) {
				if (S[j]) continue;
				g[i][j] = get_p(have[j].v1) != get_p(have[j].u1);
			}
		}

		for (int i = 0; i < m; i++) {
			if (!S[i]) continue;
			make();
			for (int j = 0; j < m; j++) {
				if (i == j) continue;
				if (!S[j]) continue;
				uni(have[j].v2, have[j].u2);
			}
			for (int j = 0; j < m; j++) {
				if (S[j]) continue;
				g[j][i] = get_p(have[j].v2) != get_p(have[j].u2);
			}
		}
	}

	void build_y() {	
		for (int i = 0; i < m; i++)
			y1[i] = y2[i] = false;

		make();
		for (int i = 0; i < m; i++) {
			if (!S[i]) continue;
			uni(have[i].v1, have[i].u1);
		}
		for (int i = 0; i < m; i++) {
			if (S[i]) continue;
			y1[i] = get_p(have[i].v1) != get_p(have[i].u1);
		}
		make();
		for (int i = 0; i < m; i++) {
			if (!S[i]) continue;
			uni(have[i].v2, have[i].u2);
		}
		for (int i = 0; i < m; i++) {
			if (S[i]) continue;
			y2[i] = get_p(have[i].v2) != get_p(have[i].u2);
		}
	}

	int w[MAXN];

	void build_w() {
		for (int i = 0; i < m; i++) 
			w[i] = (S[i] ? have[i].w : -have[i].w);

	}

	void build() {
		build_graph();
		build_y();
		build_w();
	}

	bool simple_solve() {
		int endpoint = -1;
		for (int i = 0; i < m; i++) {
			if (y1[i] && y2[i]) {
				if (endpoint == -1 || have[i].w > have[endpoint].w)
					endpoint = i;
			}
		}
		if (endpoint == -1)
			return false;
		
		S[endpoint] = true;
		ans += have[endpoint].w;
		return true;
	}

	const ll INF = 1e18;

	bool used[MAXN];
	int par[MAXN];
	ll dist[MAXN];
	int len[MAXN];

	bool smart_solve() {
		queue<int> q;
		for (int i = 0; i < m; i++)
			par[i] = -1, dist[i] = INF, used[i] = false, len[i] = m + 1;

		for (int i = 0; i < m; i++) {
			if (y1[i]) {
				q.push(i);
				used[i] = true;
				dist[i] = w[i];
				len[i] = 0;
			}
		}

		while (!q.empty()) {
			int v = q.front();
			q.pop();
			used[v] = false;
			for (int i = 0; i < m; i++) {
				if (!g[v][i]) continue;
				ll nd = w[i] + dist[v];
				ll nl = len[v] + 1;
				if (tie(dist[i], len[i]) <= tie(nd, nl)) continue;
				par[i] = v;
				dist[i] = nd;
				len[i] = nl;
				if (!used[i])
					q.push(i);
				used[i] = true;
			}
		}
	
		int endpoint = -1;
		for (int i = 0; i < m; i++) {
			if (!y2[i]) continue;
			if (dist[i] == INF) continue;
			if (endpoint == -1) {
				endpoint = i;
				continue;
			}
			if (tie(dist[endpoint], len[endpoint]) > tie(dist[i], len[i]))
				endpoint = i;
		}

		if (endpoint == -1) return false;
		while (par[endpoint] != -1) {
			S[endpoint] = S[endpoint] ^ 1;
			if (S[endpoint])
				ans += have[endpoint].w;
			else
				ans -= have[endpoint].w;
			endpoint = par[endpoint];
		}

		S[endpoint] = S[endpoint] ^ 1;
		if (S[endpoint])
			ans += have[endpoint].w;
		else
			ans -= have[endpoint].w;
		return true;
	}

	bool agment(){
		build();
		int cnt = 0;
		for (int i = 0; i < m; i++)
			cnt += S[i];
		if (cnt == 0) return simple_solve();
		return smart_solve();
	};
};

void read() {
	cin >> matroid_intersection::n >> matroid_intersection::m;
	for (int i = 0; i < matroid_intersection::m; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		a--;
		b--;
		c--;
		d--;
		matroid_intersection::have.push_back({a, b, c, d, e});
	} 
}

vector<ll> ans;

void run() {
	for (int i = 1; i <= matroid_intersection::m; i++) {
		bool flag = matroid_intersection::agment();
		if (flag)
			ans.push_back(matroid_intersection::ans);
		else {
			while (ans.size() < matroid_intersection::m)
				ans.push_back(matroid_intersection::INF);
			break;
		}
	}
}

void write() {
	for (auto i : ans) {
		if (i == matroid_intersection::INF) {
			cout << "Impossible" << "\n";
		} 
		else {
			cout << i << "\n";
		}
	}
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