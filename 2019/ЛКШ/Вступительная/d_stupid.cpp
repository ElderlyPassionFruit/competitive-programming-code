#include <bits/stdc++.h>

using namespace std;
//#define int long long
const int MAXN = 510;
int table[MAXN][MAXN];
const int INF = 1e8;
int n, m, t;

void read() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			table[i][j] = INF;
		}
	}
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> table[i][j];
		}
	}
}

vector <int> d = {0, 1, -1};

int solve(int x, int y) {
	int l = -1, r = 1e6 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int cnt = 0;

		vector <vector <bool> > used(n + 2, vector <bool> (m + 2, false));

		deque <pair <int, int> > help;
		help.push_back({x, y});

		while (!help.empty()) {
			int x = help[0].first;
			int y = help[0].second;
			help.pop_front();
			if (used[x][y])
				continue;
			//cout << x << " " << y << endl;
			used[x][y] = true;
			cnt++;

			if (cnt >= t)
				break;
			for (auto dx : d) {
				for (auto dy : d) {
					if (dx == 0 && dy == 0)
						continue;
					if (dx != 0 && dy != 0)
						continue;
					if (!used[x + dx][y + dy] && abs(table[x + dx][y + dy] - table[x][y]) <= mid) {
						help.push_back({x + dx, y + dy});
					}
				} 
			}
		}
		//cout << "l = " << l << " r = " << r << " mid = " << mid << endl;
		//cout << "cnt = " << cnt << endl;
		if (cnt >= t) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	return r;
}

int ans;
void run() {
	ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int x;
			cin >> x;
			if (x == 1){
				ans += solve(i, j);
			//	cout << "i = " << i << " j = " << j << endl;
			//	cout << solve(i, j) << endl;
			}
		}
	}
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