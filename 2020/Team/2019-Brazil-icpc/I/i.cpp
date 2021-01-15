#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct edge{
	int to, cost;
	edge() {}
	edge(int _to, int _cost) {
		to = _to, cost = _cost;
	}
};

const int MAXN = 410;
int n, m;
vector<edge> g[MAXN];
int t[MAXN];

struct event{
	int a, b, x, ind;
	event() {
		a = b = x = ind = 0;
	}
	event(int _a, int _b, int _x, int _ind) {
		a = _a, b = _b, x = _x, ind = _ind;
	}
};

int q;
const int MAXQ = 1e5 + 10;

int ans[MAXQ];
vector<event> have[2];
const int INF = 1e9 + 228;
int dp[MAXN][MAXN];
int costEdge[MAXN][MAXN];

vector<vector<int>> order;

void solve(vector<event> fq) {
	vector<vector<event>> have(order.size());
	for (auto i : fq) {
		have[min((int)order.size() - 1, i.x)].push_back(i);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = INF;
		}
		dp[i][i] = 0;
	}
	for (int k = 0; k < (int)order.size(); k++) {
		for (auto v : order[k]) {
			for (auto i : g[v]) {
				dp[i.to][v] = min(dp[i.to][v], i.cost);
				dp[v][i.to] = min(dp[v][i.to], i.cost);
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					dp[i][j] = min(dp[i][j], dp[i][v] + dp[v][j]);
				}
			}
		}
		for (auto i : have[k]) {
			int fans = min(dp[i.a][i.b], costEdge[i.a][i.b]);
			ans[i.ind] = (fans != INF ? fans : -1);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			costEdge[i][j] = INF;
		}
	}
	for (int i = 0; i < n; i++) {
		cin >> t[i];
	}
	for (int i = 0; i < m; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		u--;
		v--;
		g[u].push_back({v, cost});
		g[v].push_back({u, cost});
		costEdge[u][v] = min(costEdge[u][v], cost);
		costEdge[v][u] = min(costEdge[v][u], cost);
	}
	vector<int> allT, uniqueT;
	for (int i = 0; i < n; i++) {
		allT.push_back(t[i]);
	}
	sort(all(allT));
	uniqueT = allT;
	uniqueT.resize(unique(all(uniqueT)) - uniqueT.begin());
	cin >> q;
	for (int i = 0; i < q; i++) {
		int a, b, k, t;
		cin >> a >> b >> k >> t;
		a--;
		b--;
		k--;
		have[t].push_back({a, b, k, i});
	}
	order.assign(uniqueT.size(), {});
	for (int i = 0; i < n; i++) {
		order[lower_bound(all(uniqueT), t[i]) - uniqueT.begin()].push_back(i);
	}
	solve(have[0]);
	reverse(all(order));
	solve(have[1]);
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}