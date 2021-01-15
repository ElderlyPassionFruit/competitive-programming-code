#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 2e5 + 10;
const int INF = 1e9 + 10;
int n, m;
vector<pair<int, char>> g[MAXN];
int dist[MAXN];
queue<int> q;

void bfs() {
	fill(dist, dist + MAXN, INF);
	dist[n - 1] = 0;
	q.push(n - 1);
	while (!q.empty()) {
		int v = q.front();
		//cout << "v = " << v << endl;
		q.pop();
		for (auto i : g[v]) {
			int to = i.first;
			//cout << "to = " << to << endl;
			if (dist[to] != INF) continue;
			dist[to] = dist[v] + 1;
			q.push(to);
		}
	}
}

vector<int> ans;
int p[MAXN];
string s;

char pred[MAXN];

void bfs_ans() {
	vector<int> have;
	fill(p, p + n, -1);
	s = "";
	have.push_back(0);
	for (int i = 1; i <= dist[0]; i++) {
		vector<pair<int, int>> nxt;
		char now = 'z' + 1;
		for (auto v : have) {
			//cout << "v = " << v << endl;
			for (auto x : g[v]) {
				int to = x.first;
				char c = x.second;
				if (dist[to] + 1 != dist[v]) continue;
				if (now < c) continue;
				if (c < now) {
					nxt.clear();
					now = c;
				}
				nxt.push_back({to, v});
			}
		}
		have.clear();
		for (auto [v, par] : nxt) {
			//cout << "v, par = " << v << " " << par << endl;
			p[v] = par;
			have.push_back(v);
		}
		sort(all(have));
		have.resize(unique(all(have)) - have.begin());
		s += now;
	}
}

void make_ans() {
	int now = n - 1;
	while(p[now] != -1) {
		ans.push_back(now);
		now = p[now];
	}
	ans.push_back(now);
	reverse(all(ans));
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		u--;
		v--;
		g[u].push_back({v, c});
		g[v].push_back({u, c});
	}
	bfs();
	bfs_ans();
	make_ans();
	cout << ans.size() - 1 << "\n";
	for (auto i : ans)
		cout << i + 1 << " ";
	cout << "\n";
	cout << s << "\n";
	return 0;
}