#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define pt pair<int, int>
#define x first
#define y second

const int MAXN = 7;
int n = 7;
char a[MAXN][MAXN];
int cost[MAXN * MAXN + 10];
int color[MAXN][MAXN];

vector<int> dx = {1, 0, -1, 0};
vector<int> dy = {0, -1, 0, 1};
vector<int> dist = {1, 2, 2, 3, 3, 4};
pt s;
char now;

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

void build() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			color[i][j] = 0;
		}
	}
	queue<pt> q;
	int c = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (color[i][j]) continue;
			color[i][j] = c++;
			q.push({i, j});
			while (!q.empty()) {
				auto v = q.front();
				q.pop();
				for (int d = 0; d < 4; d++) {
					int nx = v.x + dx[d], ny = v.y + dy[d];
					if (!checkCell(nx, ny)) continue; 
					if (color[nx][ny]) continue;
					if (a[nx][ny] != a[v.x][v.y]) continue;
					color[nx][ny] = color[v.x][v.y];
					q.push({nx, ny});
				}
			}
		}
	}
	for (int i = 0; i <= c; i++) {
		cost[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] != 'P') continue;
			cost[color[i][j]]++;
		}
	}
}

map<pt, pair<pt, int>> mp;

vector<char> dir = {'N', 'W', 'S', 'E'};
void penis() {
	mp[{-1, 0}] = {{0, 1}, 0};
	mp[{-1, 1}] = {{0, 0}, 0};
	mp[{-1, 2}] = {{0, 3}, 0};
	mp[{-1, 3}] = {{0, 2}, 0};
	mp[{-1, 4}] = {{0, 5}, 0};
	mp[{-1, 5}] = {{0, 4}, 0};

	mp[{-1, 6}] = {{0, 6}, 1};
	mp[{0, 7}] = {{0, 6}, 0};

	mp[{1, 7}] = {{2, 6}, 1};
	mp[{2, 7}] = {{1, 6}, 1};
	mp[{4, 7}] = {{3, 6}, 1};
	mp[{3, 7}] = {{4, 6}, 1};
	mp[{5, 7}] = {{6, 6}, 1};
	mp[{6, 7}] = {{5, 6}, 1};

	mp[{7, 6}] = {{6, 5}, 2};
	mp[{7, 5}] = {{6, 6}, 2};
	mp[{7, 4}] = {{6, 3}, 2};
	mp[{7, 3}] = {{6, 4}, 2};
	mp[{7, 2}] = {{6, 1}, 2};
	mp[{7, 1}] = {{6, 2}, 2};
	
	mp[{7, 0}] = {{6, 0}, 3};
	mp[{6, -1}] = {{6, 0}, 2};
	
	mp[{5, -1}] = {{4, 0}, 3};
	mp[{4, -1}] = {{5, 0}, 3};
	mp[{3, -1}] = {{2, 0}, 3};
	mp[{2, -1}] = {{3, 0}, 3};
	mp[{1, -1}] = {{0, 0}, 3};
	mp[{0, -1}] = {{1, 0}, 3};
}

pt get(int dir, int dist) {
	pt now = s;
	for (int i = 0; i < dist; i++) {
		now.x += dx[dir];
		now.y += dy[dir];
		if (mp.count(now)) {
			dir = mp[now].second;
			now = mp[now].first;
		}
		assert(checkCell(now.x, now.y));
	}
	return now;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	penis();
	cin >> s.x >> s.y;
	s.x--;
	s.y--;
	//swap(s.x, s.y);
	cin >> now;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	build();
	/*cout << "color = " << endl;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			cout << color[i][j] << " ";
		}
		cout << endl;
	}
	cout << "cost = " << endl;
	for (int i = 0; i <= 4; i++) {
		cout << cost[i] << " ";
	}
	cout << endl;*/
	int pos = -1;
	for (int i = 0; i < 4; i++) {
		if (dir[i] == now) {
			pos = i;
			break;
		}
	}
	assert(pos != -1);
	//cerr << "pos = " << pos << endl;
	pair<int, char> ans;
	ans.first = 1e9;
	ans.second = 'X';
//	pt now = get(2, 1);
//	cout << "now = " << now.x << " " << now.y << endl;
//	exit(0);
//.	cout << s.x << " " << s.y << endl;
	for (int i = -1; i <= 1; i++) {
		int sum = 0;
		for (auto d : dist) {
			pt now = get((pos + 4 + i) % 4, d);
	//		cout << "now = " << now.x << " " << now.y << endl;
			sum += cost[color[now.x][now.y]];
		}
	//	cout << "sum = " << sum << " dir = " << dir[(pos + 4 + i) % 4] << endl;
		ans = min(ans, make_pair(sum, dir[(pos + 4 + i) % 4]));
	}
	cout << ans.second << endl;
	return 0;
}
