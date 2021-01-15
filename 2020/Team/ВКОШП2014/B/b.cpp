#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int get(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x -= (x + 1) / 2;
	}
	return ans;
}

const int MAXN = 12;

int edge[MAXN][MAXN];
int ed[MAXN][MAXN];

vector<int> g[MAXN];

int check(int v) {
	int fans = 0;
	for (auto i : g[v])
		fans += ed[v][i];
	return fans % 2;
}

void add(int u, int v, int cnt) {
	if (cnt == -1) ed[u][v]--;
	else ed[u][v] += get(cnt);
	if (cnt == -1) ed[v][u]--;
	else ed[v][u] += get(cnt);

	edge[u][v] += cnt;
	edge[v][u] += cnt;
}

vector<pair<int, int>> edges;

void get(int u, int v) {
	int x;
	cin >> x;
	if (x == 0) return;
	edges.push_back({u, v});
	g[u].push_back(v);
	g[v].push_back(u);
	add(u, v, x);
	//cout << u << " " << v << " " << x << endl;
}

bool used[MAXN];
vector<int> path;

void dfs(int v) {
	used[v] = true;
	path.push_back(v);
	for (auto i : g[v]) {
		if (!used[i] && ed[v][i]) {
			dfs(i);
		}
	}
}

int check() {
	for (int i = 0; i < MAXN; i++)
		used[i] = false;
	int fans = 0;
	for (int i = 0; i < MAXN; i++) {
		if (!used[i]) {
			int Ans = 0;
			path.clear();
			dfs(i);
			int cnt = 0;

			for (auto k : path)
				cnt += check(k);

			/*cout << i << " " << cnt << endl;
			cout << "path = " << endl;
			for (auto i : path)
				cout << i << " ";
			cout << endl;*/
			if (cnt != 0 && cnt != 2)
				continue;
			//cout << i << endl;
			for (auto k : path) {
				for (auto j : g[k]){
					Ans += edge[k][j];	
				}
			}
			fans = max(fans, Ans);
		}
	}
	return fans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);
	get(0, 1);
	get(1, 2);
	get(2, 3);
	get(0, 4);
	get(1, 5);
	get(2, 6);
	get(3, 7);
	get(4, 5);
	get(5, 6);
	get(6, 7);
	get(4, 8);
	get(5, 9);
	get(6, 10);
	get(7, 11);	
	get(8, 9);
	get(9, 10);
	get(10, 11);

	int ans = 0;

	for (int mask = 0; mask < (1 << edges.size()); mask++) {
		for (int i = 0; i < edges.size(); i++) {
			if ((mask >> i) & 1) {
				add(edges[i].first, edges[i].second, -1);
			}
		}
		ans = max(ans, check());
		for (int i = 0; i < edges.size(); i++) {
			if ((mask >> i) & 1) {
				add(edges[i].first, edges[i].second, 1);
			}
		}
	}
	cout << ans / 2 << endl;
	return 0;
}

/*
1 2 3
4 5 6 7
8 9 10
11 12 13 14
15 16 17


1 1 1
0 0 0 0
1 1 1
0 0 0 1
1 1 1
*/