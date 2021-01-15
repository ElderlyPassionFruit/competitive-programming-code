#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 1010;
const int INF = 1e9;
int dp[MAXN][MAXN];
char table[MAXN][MAXN];
int NEXT[MAXN][MAXN][4];
int n, m;
pair <int, int> s, c;

void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = INF;
			table[i][j] = '#';
			for (int k = 0; k < 4; k++)
				NEXT[i][j][k] = -1;
		}
	}
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'S')
				s = {i, j};
			if (table[i][j] == 'C')
				c = {i, j};
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (table[i][j] == '#')
				NEXT[i][j][0] = j;
			else
				NEXT[i][j][0] = NEXT[i][j - 1][0];
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = m + 1; j >= 1; j--) {
			if (table[i][j] == '#') 
				NEXT[i][j][2] = j;
			else
				NEXT[i][j][2] = NEXT[i][j + 1][2];
		}
	}

	for (int j = 1; j <= m; j++) {
		for (int i = 0; i <= n; i++) {
			if (table[i][j] == '#')
				NEXT[i][j][1] = i;
			else
				NEXT[i][j][1] = NEXT[i - 1][j][1];
		}
	}

	for (int j = 1; j <= m; j++) {
		for (int i = n + 1; i >= 1; i--) {
			if (table[i][j] == '#')
				NEXT[i][j][3] = i;
			else
				NEXT[i][j][3] = NEXT[i + 1][j][3];
		}
	}
}

#define x first
#define y second
set <pair <int, pair <int, int> > > q;

void relax(pair <int, int> v, int dx, int dy, int dist) {
	if (table[v.x + dx][v.y + dy] != '#') {
		if (dp[v.x + dx][v.y + dy] > dist + 1) {
			q.erase({dp[v.x + dx][v.y + dy], {v.x + dx, v.y + dy}});
			dp[v.x + dx][v.y + dy] = dist + 1;
			q.insert({dp[v.x + dx][v.y + dy], {v.x + dx, v.y + dy}});
		}
	}
}

void relax2(pair <int, int> v, pair <int, int> to, int dist) {
	if (dp[to.x][to.y] > dist + 1) {
		q.insert({dp[to.x][to.y], to});
		dp[to.x][to.y] = dist + 1;
		q.insert({dp[to.x][to.y], to});
	}
}

int d[MAXN][MAXN];

deque <pair <int, pair <int, int> > > f;

void relax3(pair <int, int> v, int dx, int dy, int dist) {
	if (table[v.x + dx][v.y + dy] != '#') {
		if (d[v.x + dx][v.y + dy] > dist + 1) {
			//q.erase({dp[v.x + dx][v.y + dy], {v.x + dx, v.y + dy}});
			d[v.x + dx][v.y + dy] = dist + 1;
			f.push_back({d[v.x + dx][v.y + dy], {v.x + dx, v.y + dy}});
		}
	}
}

bool check(int x, int y) {
	return table[x][y] == '#';
}

void bfs() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			d[i][j] = INF;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			bool flag = check(i + 1, j) || check(i - 1, j) || check(i, j + 1) || check(i, j - 1);
			if (flag && table[i][j] != '#') {
				d[i][j] = 0;
				f.push_back({0, {i, j}});
			}
		}
	}


	while (!f.empty()) {
		auto p = f[0];
		f.pop_front();
		int dist = p.first;
		pair <int, int> v = p.second;
		relax3(v, 1, 0, dist);
		relax3(v, -1, 0, dist);
		relax3(v, 0, 1, dist);
		relax3(v, 0, -1, dist);
	}
}

void run() {
	/*cout << "NEXT = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << NEXT[i][j][0] << " ";
		}
		cout << endl;
	}
cout << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << NEXT[i][j][1] << " ";
		}
		cout << endl;
	}
cout << endl;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << NEXT[i][j][2] << " ";
		}
		cout << endl;
	}
cout << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << NEXT[i][j][3] << " ";
		}
		cout << endl;
	}
cout << endl;*/
	bfs();

	dp[s.first][s.second] = 0;

	q.insert({0, s});
	while (!q.empty()) {
		auto p = *q.begin();
		q.erase(q.begin());
		int dist = p.first;
		pair <int, int> v = p.second;

		int D = d[v.x][v.y];
		relax(v, 1, 0, dist);
		relax(v, 0, 1, dist);
		relax(v, -1, 0, dist);
		relax(v, 0, -1, dist);

		pair <int, int> to = {v.x, NEXT[v.x][v.y][0] + 1};
		relax2(v, to, dist + D);
		to = {v.x, NEXT[v.x][v.y][2] - 1};
		relax2(v, to, dist + D);
		to = {NEXT[v.x][v.y][1] + 1, v.y};
		relax2(v, to, dist + D);
		to = {NEXT[v.x][v.y][3] - 1, v.y};
		relax2(v, to, dist + D);
	}
	/*cout << "dp =" << endl;
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= m + 1; j++) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}
*/
	/*for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}

*/
}

void write() {
	cout << dp[c.first][c.second] << endl;
}

signed main() {
	freopen("portals.in", "r", stdin);
	freopen("portals.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}