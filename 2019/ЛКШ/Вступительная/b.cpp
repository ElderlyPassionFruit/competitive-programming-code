#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 20010;
const int MAXK = 210;
const int INF = 1e9 + 10;

int n, m, k, q;
vector <pair <int, int> > g[MAXN][2];
unordered_set <int> hubs;

void read() {
	cin >> n >> m >> k >> q;
	for (int i = 0; i < m; i++) {
		int u, v, d;
		cin >> u >> v >> d;
		u--;
		v--;
		g[u][0].push_back({v, d});
		g[v][1].push_back({u, d});
	}
	for (int i = 0; i < n; i++) {
		g[i][0].push_back({i, 0});
		g[i][1].push_back({i, 1});
	}
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		x--;
		hubs.insert(x);
	}
}

int dist[MAXK][MAXK];
unordered_map <int, int> vert;

void make() {
	int cnt = 0;
	for (auto i : hubs) {
		vert[i] = cnt++;
	}
	
	for (int i = 0; i < MAXK; i++) {
		for (int j = 0; j < MAXK; j++) {
			dist[i][j] = INF;
			if (i == j)
				dist[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++) {
		if (hubs.count(i)) {
			for (auto j : g[i][0]) {
				if (hubs.count(j.first)) {
					dist[vert[i]][vert[j.first]] = min(dist[vert[i]][vert[j.first]], j.second);
				}
			}
		}
		else {
			for (auto j : g[i][0]) {
				if (hubs.count(j.first) == 0)
					continue;
				for (auto l : g[i][1]) {
					if (hubs.count(l.first) == 0)
						continue;
					dist[vert[l.first]][vert[j.first]] = min(dist[vert[l.first]][vert[j.first]], l.second + j.second);
				}
			}
		}
	}

	for (int x = 0; x < k; x++) {
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				dist[i][j] = min(dist[i][j], dist[i][x] + dist[x][j]);
			}
		}
	}
}

vector <int> solve(int a, vector <int> b) {
	vector <int> local_dist(k, INF);

	for (auto i : g[a][0]) {
		if (vert.count(i.first)) {
			local_dist[vert[i.first]] = min(local_dist[vert[i.first]], i.second);
			for (int j = 0; j < k; j++) {
				local_dist[j] = min(local_dist[j], local_dist[vert[i.first]] + dist[vert[i.first]][j]);
			}
		}
	}

	/*cout << "a = " << a << endl;
	cout << "b = ";
	for (auto i : b)
		cout << i << " ";
	cout << endl;

	cout << "local_dist = ";
	for (auto i : local_dist) {
		cout << i << " ";
	}
	cout << endl;*/

	vector <int> ans;
	for (auto i : b) {
		int fans = INF;
		
		if (vert.count(i)) {
			fans = local_dist[vert[i]];
		}
		
		if (i == a)
			fans = 0;
		
		for (auto j : g[i][1]) {
			if (vert.count(j.first)) {
				fans = min(fans, local_dist[vert[j.first]] + j.second);
			}
		}

		if (fans != INF)
			ans.push_back(fans);
	}

	return ans;
}

int cnt, sum;

void run() {
	make();
	/*cout << endl;
	cout << "vert = " << endl;
	for (auto i : vert) {
		cout << i.first << " " << i.second << endl;
	}

	cout << endl;
	cout << "dist = " << endl;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << dist[i][j] << " ";
		}
		cout << endl;
	}
*/

 	cnt = 0;
	sum = 0;
	map <int, vector <int> > help;
	for (int test = 0; test < q; test++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		help[a].push_back(b);
	}
	for (auto i : help) {
	//	cout << "i = " << i.first << endl;
	//	for (auto j : i.second)
	//		cout << j << " ";
	//	cout << endl;
		auto p = solve(i.first, i.second);
	//	cout << "p = " << endl;
	//	for (auto j : p)
	//		cout << j << " ";
	//	cout << endl;
		cnt += p.size();
		for (auto j : p) {
			sum += j;
		}
	}
}

void write() {
	cout << cnt << endl;
	cout << sum << endl;
}

signed main() {
	freopen("vacationgold.in", "r", stdin);
	freopen("vacationgold.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}