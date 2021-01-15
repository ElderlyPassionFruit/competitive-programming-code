#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 3e5 + 10;

vector<int> g[MAXN];
set<int> p;
int n, k, d;
map <pair <int, int>, int> roads;

void read() {
	cin >> n >> k >> d;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		p.insert(x - 1);
	}
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
		roads[{min(u, v), max(u, v)}] = i + 1;
	}
}

set<int> ans;

void bfs() {
	vector<bool> used(n, 0);
	deque<pair <int, int> > q;
	for (auto i : p) {
		q.push_back({i, i});
		used[i] = true;
	}

	while (!q.empty()) {
		int v = q[0].first;
		int p = q[0].second;
		q.pop_front();
		for (auto i : g[v]) {
			if (i != p) {
				if (used[i]) {
					ans.insert(roads[{min(i, v), max(i, v)}]);
				}
				else {
					used[i] = true;
					q.push_back({i, v});
				}
			}
		}
	}
}

void run() {
	bfs();
}

void write() {
	cout << ans.size() << "\n";
	for (auto i : ans)
		cout << i << " ";
	cout << "\n";
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