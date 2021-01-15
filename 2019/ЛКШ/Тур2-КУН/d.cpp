#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 510;
int m;
vector<int> g[MAXN];

int minuts() {
	int ans = 0;
	char x;
	cin >> x;
	ans += x - '0';
	cin >> x;
	ans *= 10;
	ans += x - '0';
	ans *= 60;
	cin >> x;
	cin >> x;
	ans += (x - '0') * 10;
	cin >> x;
	ans += x - '0';
	return ans;
}

vector<vector<int> > help;

void read() {
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x = minuts();
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		help.push_back({x, a, b, c, d});
	}
}

int dist(int i) {
	return abs(help[i][1] - help[i][3]) + abs(help[i][2] - help[i][4]);
}

int dist(int i, int j) {
	return abs(help[i][3] - help[j][1]) + abs(help[i][4] - help[j][2]);
}

bool check(int i, int j) {
	if (dist(i) + help[i][0] + dist(i, j) < help[j][0])
		return true;
	return false;
}

int used[MAXN], mt[MAXN];

bool dfs(int v, int c) {
	if (used[v] == c) return false;
	used[v] = c;
	for (auto i : g[v]) {
		if (mt[i] == -1) {
			mt[i] = v;
			return true;
		}
	}
	for (auto i : g[v]) {
		if (dfs(mt[i], c)) {
			mt[i] = v;
			return true;
		}
	}
	return false;
}

int ans;

void run() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			if (i == j) continue;
			if (check(i, j)) {
				g[i].push_back(j);
			}
		}
	}

	for (int i = 0; i < m; i++) {
		used[i] = -1;
		mt[i] = -1;
	}

	for (int i = 0; i < m; i++) {
		dfs(i, i);
	}

	ans = 0;
	for (int i = 0; i < m; i++) {
		ans += mt[i] != -1;
	}
	ans = m - ans;
}

void write() {
	//cerr << ans;
	cout << ans << endl;
}

signed main() {
	/*freopen("taxi.in", "r", stdin);
	freopen("taxi.out", "w", stdout);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);*/
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}

/*
2
08:00 10 11 9 16
08:07 9 16 10 11

2
08:00 10 11 9 16
08:06 9 16 10 11
*/