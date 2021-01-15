#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10, MAXK = 4;
vector<int> g[MAXN];
int n, m, k;
int a[MAXK];

void read() {
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		cin >> a[i];
		a[i]--;
	}	
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
}

int dist[MAXK][MAXN];

void build(int ind) {
	fill(dist[ind], dist[ind] + n, -1);
	dist[ind][a[ind]] = 0;
	queue<int> q;
	q.push(a[ind]);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto i : g[v]) {
			if (dist[ind][i] != -1) continue;
			dist[ind][i] = dist[ind][v] + 1;
			q.push(i);
		}
	}
}

int ans;

void relax(vector<int> & par, vector<int> & now) {
	int fans = 0;
	for (int i = 0; i < k; i++) {
		int v = now[i];
		if (par[v] == -1) {
			fans += dist[v][0];
		} else {
			fans += dist[v][a[par[v]]];
		}
	}
	chkmin(ans, fans);
	if (fans == 0) {
		cout << "par = " << endl;
		for (auto i : par) {
			cout << i << " ";
		}
		cout << endl;
		cout << "now = " << endl;
		for (auto i : now) {
			cout << i << " ";
		}
		cout << endl;
		exit(0);
	}
}

void relax(vector<int> & have) {
	vector<int> now(k);
	iota(all(now), 0);
	do {
		relax(have, now);
	} while (next_permutation(all(now)));
}

void gen(vector<int> have) {
	if (have.size() == k) {
		relax(have);
		return;
	}
	have.push_back(-1);
	for (int i = 0; i < (int)have.size(); i++) {
		gen(have);
		have[have.size() - 1]++;
	}
}

void run() {
	for (int i = 0; i < k; i++) {
		build(i);
		cout << "dist = " << endl;
		for (int v = 0; v < n; v++) {
			cout << dist[i][v] << " ";
		}
		cout << endl;
	}
	ans = n * 100;
	gen({});
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