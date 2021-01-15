#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int a, int b) {
		x = a, y = b;
	}
};

bool operator<(const pt & a, const pt & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

struct event{
	int d;
	pt a;
	event() {}
	event(int x, pt y) {
		d = x, a = y;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.d, a.a) < tie(b.d, b.a);
}

const int INF = 1e9;
const int MAXN = 510;
char table[MAXN][MAXN];
int w, h;
int n;
pt s;

bool check(int x, int y) {
	return x >= 1 && x <= h && y >= 1 && y <= w;
}

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};
vector<char> nxt = {'N', 'E', 'S', 'W'};

int dist[MAXN][MAXN];
char p[MAXN][MAXN];

void clear() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dist[i][j] = INF;
		}
	}
}

string solve1() {
	clear();
	set<event> q;
	dist[s.x][s.y] = 0;
	q.insert({0, s});
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		for (int i = 0; i < 4; i++) {
			int nx = v.a.x + dx[i];
			int ny = v.a.y + dy[i]; 
			if (!check(nx, ny)) continue;
			if (dist[nx][ny] > v.d + 1) {
				q.erase({dist[nx][ny], {nx, ny}});
				dist[nx][ny] = v.d + 1;
				p[nx][ny] = nxt[i];
				q.insert({dist[nx][ny], {nx, ny}});
			}
		}
	}

	pair <int, pt> ans = {INF, {}};
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (table[i][j] == 'T') {
				ans = min(ans, make_pair(dist[i][j], pt(i, j)));
			}
		}
	}

	pt f = ans.second;
	string fout = "";
	while (f.x != s.x || f.y != s.y) {
		fout += p[f.x][f.y];
		for (int i = 0; i < 4; i++) {
			if (p[f.x][f.y] == nxt[i]) {
				f.x -= dx[i];
				f.y -= dy[i];
				break;
			}
		}
	}
	f = ans.second;

	reverse(all(fout));
	for (int i = 0; i < 4; i++) {
		if (check(f.x + dx[i], f.y + dy[i])) {
			for (int j = 0; j < n - 1; j++) {
				fout += nxt[i];
				fout += nxt[i ^ 2];
			}
			break;
		}
	}
	return fout;
}

string solve2() {
	clear();
	set<event> q;
	dist[s.x][s.y] = 0;
	q.insert({0, s});
	while (!q.empty()) {
		auto v = *q.begin();
		q.erase(q.begin());
		for (int i = 0; i < 4; i++) {
			int nx = v.a.x + dx[i];
			int ny = v.a.y + dy[i]; 
			if (!check(nx, ny)) continue;
			if (dist[nx][ny] > v.d + 1 - (table[nx][ny] == 'T')) {
				q.erase({dist[nx][ny], {nx, ny}});
				dist[nx][ny] = v.d + 1 - (table[nx][ny] == 'T');
				p[nx][ny] = nxt[i];
				q.insert({dist[nx][ny], {nx, ny}});
			}
		}
	}

	pair <pair<int, int>, pt> ans = {{INF, INF}, {}};
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			if (table[i][j] == 'T') {
				bool flag = false;
				for (int k = 0; k < 4; k++) {
					if (!check(i + dx[k], j + dy[k])) continue;
					flag |= (table[i + dx[k]][j + dy[k]] == 'T');
				}
				if (!flag) continue;
				ans = min(ans, make_pair(make_pair(dist[i][j], abs(s.x - i) + abs(s.y - j)), pt(i, j)));
			}
		}
	}

	if (ans.first.first == INF)
		return "-1";

	pt f = ans.second;
	string fout = "";
	int x = 0;
	while (f.x != s.x || f.y != s.y) {
		fout += p[f.x][f.y];
		x += table[f.x][f.y] == 'T';
		for (int i = 0; i < 4; i++) {
			if (p[f.x][f.y] == nxt[i]) {
				f.x -= dx[i];
				f.y -= dy[i];
				break;
			}
		}
	}
	n -= x;
	f = ans.second;

	reverse(all(fout));
	//cout << "fout = " << fout << endl;
	//cout << n << endl;
	for (int i = 0; i < 4; i++) {
		if (check(f.x + dx[i], f.y + dy[i]) && table[f.x + dx[i]][f.y + dy[i]] == 'T') {
			for (int j = 0; j + 1 < n; j += 2) {
				//cout << j << endl;
				fout += nxt[i];
				fout += nxt[i ^ 2];
			}
			if (n % 2 != 0) {
				fout += nxt[i];
			}
			break;
		}
	}
	return fout;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	cin >> w >> h >> n;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			cin >> table[i][j];
			if (table[i][j] == 'V')
				s = {i, j};
		}
	}

	string ans1 = solve1();
	string ans2 = solve2();
	//cout << ans1 << " " << ans2 << endl;
	if (ans2 != "-1") {
		if (ans1.size() >= ans2.size())
			ans1 = ans2;
	}
	cout << ans1 << endl;
	return 0;
}









