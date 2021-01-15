#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 510;

int n, m;
char a[MAXN][MAXN];
int ans[MAXN][MAXN];
bool used[MAXN][MAXN];

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			ans[i][j] = -1;
		}
	}
}

vector<char> lett = {'P', 'W', 'G'};
vector<int> dx = {-1, -1, -1, 0, 1, 1, 1, 0};
vector<int> dy = {-1, 0, 1, 1, 1, 0, -1, -1};
vector<char> fout = {'\\', '|', '/', '-', '\\', '|', '/', '-'};

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

bool check(int x, int y, int dx, int dy) {
	for (int i = 0; i < 3; i++) {
		if (!check(x, y)) return false;
		if (used[x][y]) return false;
		if (lett[i] != a[x][y]) return false;
		x += dx;
		y += dy;
	}
	return true;
}

mt19937 rnd(time(0));

set<int> g[MAXN * MAXN];
vector<int> have[MAXN * MAXN];

int cnt = 0;

void add(int x, int y, int dx, int dy) {
	int v = cnt++;
	for (int i = 0; i < 3; i++) {
		g[x * m + y].insert(v);
		have[v].push_back(x * m + y);
		x += dx;
		y += dy;
	}
}

set<int> now;

bool check_add(int v) {
	for (auto i : have[v]) {
		for (auto j : g[i]) {
			if (now.count(j)) {
				return false;
			}
		}
	}
	return true;
}

void build() {
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			for (int i = 0; i < 8; i++) {
				if (check(x, y, dx[i], dy[i])) {
					add(x, y, dx[i], dy[i]);
				}
			}
		}
	}
	vector<int> fadd(cnt);
	iota(all(fadd), 0);
	shuffle(all(fadd), rnd);
	for (auto i : fadd) {
		if (check_add(i)) {
			now.insert(i);
		}
	}
}

void rebuild(int x) {
	auto it = now.lower_bound(x);
	if (it == now.end()) it = now.begin();
	int v = *it;
	//cerr << v << endl;
	now.erase(v);
	int cnt = 0;
	for (auto i : have[v]) {
		for (auto j : g[i]) {
			if (j == v) continue;
			if (check_add(j)) {
				cnt++;
				now.insert(j);
			}
		}
	}
	//cerr << now.size() << endl;
	if (cnt == 0) now.insert(v);
}

void add_ans(int ind) {
	int nx = 0, ny = 0;
	int my = 0;
	for (auto i : have[ind]) {
		nx += i / m;
		ny += i % m;
		if (a[i / m][i % m] == 'P')
		my = i;
	}
	nx /= 3;
	ny /= 3;
	for (int i = 0; i < 8; i++) {
		int v = (nx + dx[i]) * m + (ny + dy[i]);
		if (v == my) {
			ans[nx][ny] = i;
			break;
		}
	}
}

void run() {
	build();
	for (int it = 0; it < 100000000; it++) {
		int x = rnd() % cnt;
		if (it % 10000 == 0) cerr << now.size() << endl;
		rebuild(x);
		if (now.size() >= 46470) break;
	}
	/*for (int it = 0; it < 100000000; it++) {
		cerr << now.size() << endl;
		
		vector<int> have;
		for (auto i : now) have.push_back(i);
		for (auto x : have)
			rebuild(x);
		if (now.size() >= 472216) break;
	}*/
	/*cout << "now = " << endl;
	for (auto i : now) {
		cout << i / m << " " << i % m << endl;
	}*/
	for (auto i : now) {
		add_ans(i);
	}
	cerr << now.size() << endl;
}

void write() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans[i][j] == -1) cout << a[i][j];
			else cout << fout[ans[i][j]];
		}
		cout << "\n";
	}
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