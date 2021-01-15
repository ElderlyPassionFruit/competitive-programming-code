#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 110;
int n, m;
char a[MAXN][MAXN];
vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
}

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int color[MAXN][MAXN];
int c = 1;

void bfs() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (color[i][j]) continue;
			if (a[i][j] == '.') continue;
			color[i][j] = c++;
			queue<pair<int, int>> q;
			q.push({i, j});
			while (!q.empty()) {
				auto v = q.front();
				q.pop();
				for (int d = 0; d < 4; d++) {
					int nx = v.first + dx[d], ny = v.second + dy[d];
					if (!checkCell(nx, ny)) continue;
					if (a[nx][ny] == '.') continue;
					if (color[nx][ny]) continue;
					color[nx][ny] = color[v.first][v.second];
					q.push({nx, ny});
				}
			}
		}
	}
}

int cnt[MAXN * MAXN];
int mnX[MAXN * MAXN], mxX[MAXN * MAXN], mnY[MAXN * MAXN], mxY[MAXN * MAXN];

void makeAns() {
	for (int i = 1; i <= c; i++) {
		cnt[i] = 0;
		mnX[i] = mnY[i] = 1e9;
		mxX[i] = mxY[i] = -1e9;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!color[i][j]) continue;
			int c = color[i][j];
			cnt[c]++;
			mnX[c] = min(mnX[c], i);
			mxX[c] = max(mxX[c], i);
			mnY[c] = min(mnY[c], j);
			mxY[c] = max(mxY[c], j);
		}
	}
	int ansH = 0, ansW = 0, ansS = 0;
	for (int i = 1; i <= c; i++) {
		int sq = (mxX[i] - mnX[i] + 1) * (mxY[i] - mnY[i] + 1);
		if (sq != cnt[i]) continue;
		if (mxX[i] - mnX[i] > mxY[i] - mnY[i]) {
			ansH++;
		} else if (mxX[i] - mnX[i] < mxY[i] - mnY[i]) {
			ansW++;
		} else {
			ansS++;
		}
	}
	cout << ansH << " " << ansW << " " << ansS << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	read();
	bfs();
	makeAns();
	return 0;
}