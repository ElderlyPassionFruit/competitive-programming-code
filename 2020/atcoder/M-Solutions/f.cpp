#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

const int N = 2e5 + 10;
const int INF = 1e9 + 228;
int n;
vector<pt> a[4];
int ans = INF;
vector<int> fx[N][4];
vector<int> fy[N][4];
map<int, vector<int>> have[2];

int get(char x) {
	if (x == 'U') return 0;
	if (x == 'R') return 1;
	if (x == 'D') return 2;
	if (x == 'L') return 3;
	assert(false);
	return -1;
}

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		char t;
		cin >> x >> y >> t;
		a[get(t)].push_back({x, y});
	}
}

void solveOneDir(vector<int> & a, vector<int> & b, int add) {
	sort(all(a));
	sort(all(b));
	for (auto i : a) {
		int pos = lower_bound(all(b), i) - b.begin();
		if (pos == (int)b.size()) continue;
		chkmin(ans, add * (b[pos] - i));
	}
}

void solvePerpDir(vector<pt> & u, vector<pt> & r) {
	have[0].clear();
	have[1].clear();
	for (auto [x, y] : u) {
		have[0][x + y].push_back(x);
	}
	for (auto [x, y] : r) {
		have[1][x + y].push_back(x);
	}
	for (auto i : have[1]) {
		if (!have[0].count(i.first)) continue;
		solveOneDir(i.second, have[0][i.first], 10);
	}
}

void make(vector<pt> & a, int t) {
	for (auto &[x, y] : a) {
		if (t == 0) x = -x;
		else if (t == 1) y = -y;
	}
}

void run() {
	for (int i = 0; i < 4; i++) {
		for (auto [x, y] : a[i]) {
			fx[x][i].push_back(y);
			fy[y][i].push_back(x);
		}
	}
	for (int i = 0; i < N; i++) {
		solveOneDir(fx[i][0], fx[i][2], 5);
		solveOneDir(fy[i][1], fy[i][3], 5);
	}
	solvePerpDir(a[0], a[1]);
	make(a[1], 1);
	make(a[2], 1);
	solvePerpDir(a[2], a[1]);
	make(a[0], 0);
	make(a[3], 0);
	solvePerpDir(a[0], a[3]);
	make(a[3], 1);
	make(a[2], 0);
	solvePerpDir(a[2], a[3]);
}

void write() {
	if (ans == INF) {
		cout << "SAFE" << endl;
	} else {
		cout << ans << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}