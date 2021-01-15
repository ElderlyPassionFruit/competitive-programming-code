#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
};

int dist(const pt & a, const pt & b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

const int N = 1e5 + 10, W = 1e3 + 10;
int w, h;
int n;
pt a[N];

bool checkCell(int x, int y) {
	return x >= 1 && x <= w && y >= 1 && y <= h;
}

vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};

int my[W][W];
queue<pt> q;

void relax(int x, int y, int val) {
	if (my[x][y] != -1) return;
	my[x][y] = val;
	q.push({x, y});
}

void bfs() {
	for (int i = 1; i <= w; i++) {
		for (int j = 1; j <= h; j++) {
			my[i][j] = -1;
		}
	}
	for (int i = 0; i < n; i++) {
		relax(a[i].x, a[i].y, i);
	}
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		for (int it = 0; it < 4; it++) {
			int nx = v.x + dx[it];
			int ny = v.y + dy[it];
			if (!checkCell(nx, ny)) continue;
			relax(nx, ny, my[v.x][v.y]);
		}
	}
}

struct Romb{
	int lSum, rSum, lDiff, rDiff;
	Romb() {}
	Romb(int x, int y, int len) {
		lSum = x + y - len;
		rSum = x + y + len;
		lDiff = x - y - len;
		rDiff = x - y + len;
	}
};

Romb merge(Romb a, Romb b) {
	Romb ans;
	ans.lSum = max(a.lSum, b.lSum);
	ans.rSum = min(a.rSum, b.rSum);
	ans.lDiff = max(a.lDiff, b.lDiff);
	ans.rDiff = min(a.rDiff, b.rDiff);
	return ans; 
}

bool check(int len) {
	Romb now = Romb(1, 1, 1e9);
	for (int x = 1; x <= w; x++) {
		for (int y = 1; y <= h; y++) {
			if (dist({x, y}, a[my[x][y]]) <= len) continue;
			now = merge(now, Romb(x, y, len));			
		}
	}
	for (int x = 1; x <= w; x++) {
		for (int y = 1; y <= h; y++) {
			int sum = x + y;
			int diff = x - y;
			if (now.lSum > sum) continue;
			if (now.rSum < sum) continue;
			if (now.lDiff > diff) continue;
			if (now.rDiff < diff) continue;
			return true;
			//cout << x << " " << y << endl;
			//exit(0);
		}
	}
	return false;
	//return now.lSum <= now.rSum && now.lDiff <= now.rDiff;
}

void makeAns(int len) {
	cout << len << endl;
	Romb now = Romb(1, 1, 1e9);
	for (int x = 1; x <= w; x++) {
		for (int y = 1; y <= h; y++) {
			if (dist({x, y}, a[my[x][y]]) <= len) continue;
			now = merge(now, Romb(x, y, len));			
		}
	}
	//cout << now.lDiff << " " << now.rDiff <<  
	for (int x = 1; x <= w; x++) {
		for (int y = 1; y <= h; y++) {
			int sum = x + y;
			int diff = x - y;
			if (now.lSum > sum) continue;
			if (now.rSum < sum) continue;
			if (now.lDiff > diff) continue;
			if (now.rDiff < diff) continue;
			cout << x << " " << y << endl;
			exit(0);
		}
	}
	assert(false);
}

signed main() {
	freopen("lights.in", "r", stdin);
	freopen("lights.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> w >> h;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	bfs();
	int l = -1, r = w + h;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	//cout << "r = " << r << endl;
	makeAns(r);
	return 0;
}