#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 210;
string t;
int n, m, q;
char a[MAXN][MAXN];

struct event{
	int t, x, y, len, need;
	event() {}
	event(int _t, int _x, int _y, int _len, int _need) {
		t = _t, x = _x, y = _y, len = _len, need = _need;
	}
};

vector<event> have;

void read() {
	cin >> t;
	cin >> n >> m >> q;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	have.resize(q);
	for (auto &[t, x, y, len, need] : have) {
		cin >> t >> x >> y >> len >> need;

	}
}

vector<int> cell[MAXN][MAXN];

vector<int> dx = {0, 1}, dy = {1, 0};
map<vector<int>, vector<pair<int, int>>> same;

void make() {
	for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) cell[i][j].clear();
	same.clear();
	int ind = 0;
	for (auto [t, x, y, len, need] : have) {
		for (int i = 0; i < len; i++) {
			cell[x + i * dx[t - 1]][y + i * dy[t - 1]].push_back(ind);
		}
		ind++;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			sort(all(cell[i][j]));
			same[cell[i][j]].push_back({i, j});
		}
	}
}

mt19937 rnd(time(0));

int ans[MAXN][MAXN];

int get_rand_divizor(int x) {
	vector<int> have;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			have.push_back(i);
			have.push_back(x / i);
		}
	}
	int pos = rnd() % (int)have.size();
	pos += (int)have.size();
	pos %= (int)have.size();
	return have[pos];
}

int get(int ind) {
	int num = 1;
	for (int i = 0; i < have[ind].len; i++) {
		int x = have[ind].x + i * dx[have[ind].t - 1];
		int y = have[ind].y + i * dy[have[ind].t - 1];
		num *= ans[x][y];
	}
	return num;
}

bool check(int ind) {
	return get(ind) == have[ind].need;
} 

bool try_to_make() {
	queue<int> bad;
	//cerr << "puhh" << endl;
	for (int i = 0; i < (int)have.size(); i++) {
		if (!check(i)) {
			bad.push(i);
		}
	}
	//cerr << "puhh" << endl;
	int it = 0;
	while (it < 10000 && !bad.empty()) {
		
		/*cerr << "ans = " << endl;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cerr << ans[i][j] << " ";
			}
			cerr << endl;
		}*/
		/*if (it % 1000 == 0) {
			cerr << "try = " << it << endl;
		}*/
		it++;
		int ind = bad.front();
		bad.pop();
		//cerr << "ind = " << ind << endl;
		int num = get(ind);
		//cerr << "num = " << num << " have[ind] = " << have[ind].need << endl;
		if (num == have[ind].need) continue;
		if (num < have[ind].need) {
			int len = rnd() % have[ind].len;
			int x = have[ind].x + len * dx[have[ind].t - 1];
			int y = have[ind].y + len * dy[have[ind].t - 1];
			ans[x][y] *= have[ind].need / num;
			for (auto fcheck : cell[x][y]) {
				if (!check(fcheck)) {
					bad.push(fcheck);
				}
			}
		} else {
			num /= have[ind].need;
			for (int i = 0; i < have[ind].len; i++) {
				int x = have[ind].x + i * dx[have[ind].t - 1];
				int y = have[ind].y + i * dy[have[ind].t - 1];
				int g = __gcd(ans[x][y], num);
				ans[x][y] /= g;
				num /= g;
				for (auto fcheck : cell[x][y]) {
					if (!check(fcheck)) {
						bad.push(fcheck);
					}
				}	
			}
		}
	}
	return bad.empty();
}

void start() {
	vector<pair<int, int>> need;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (a[i][j] == '#') continue;
			need.push_back({i, j});
		}
	}
	for (int it = 0; it < 10000; it++) {
		if (it % 1000 == 0)
		cerr << "it1 = " << it++ << endl;
		shuffle(all(need), rnd);
		vector<int> now;
		for (auto i : have) {
			now.push_back(i.need);
		}
		
		for (auto [x, y] : need) {
			int val = 0;
			for (auto i : cell[x][y]) {
				val = __gcd(val, now[i]);
			}
			val = get_rand_divizor(val);
			for (auto i : cell[x][y]) {
				now[i] /= val;
			}
			if (val == 0) val = 1;
			ans[x][y] = val;
		}

		for (auto [x, y] : need) {
			int val = 0;
			for (auto i : cell[x][y]) {
				val = __gcd(val, now[i]);
			}
			for (auto i : cell[x][y]) {
				now[i] /= val;
			}
			if (val == 0) val = 2;
			ans[x][y] *= val;
		}

		if (!try_to_make()) continue;
		bool ok = true;
		for (auto i : now) {
			ok &= i == 1;
		}
		if (ok) break;
	}
	cerr << "start :: make" << endl;
}

vector<int> factor(int x) {
	vector<int> ans;
	for (int i = 2; i * i <= x; i++) {
		while (x % i == 0) {
			ans.push_back(i);
			x /= i;
		}
	}
	if (x > 1) {
		ans.push_back(x);
	}
	return ans;
}

void make(int i, int j) {
	vector<int> have;
	shuffle(all(same[cell[i][j]]), rnd);
	for (auto [x, y] : same[cell[i][j]]) {
		auto now = factor(ans[x][y]);
		for (auto it : now) {
			have.push_back(it);
		}
		ans[x][y] = 1;
	}
	/*cout << "have = " << endl;
	for (auto i : have) {
		cout << i << " ";
	}
	cout << endl;*/
	shuffle(all(have), rnd);
	/*cout << "same = " << endl;
	for (auto [x, y] : same[cell[i][j]]) {
		cout << x << " " << y << endl;
	}
	cout << endl;*/
	for (int it = 0; it < (int)have.size(); it++) {
		int x = same[cell[i][j]][it % (int)size(same[cell[i][j]])].first;
		int y = same[cell[i][j]][it % (int)size(same[cell[i][j]])].second;
		ans[x][y] *= have[it];
	}
	//exit(0);
}

void reshuffle() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ans[i][j] != 1) continue;
			make(i, j);
		}
	}
}

void solve() {
	start();
	for (int i = 0; i < 100; i++) {
		if (i % 1000 == 0)
			cerr << "it = " << i << endl;
		reshuffle();
	}
	//cout << "make = " << endl;
	//make(3, 1);
}

void run() {
	make();
	/*cout << "same = " << endl;
	for (auto i : same) {
		for (auto j : i.second) {
			cout << j.first << " " << j.second << " | ";
		}
		cout << endl;
	}
	cout << "cell = " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << "i, j = " << i << " " << j << endl;
			for (auto x : cell[i][j]) {
				cout << x << " ";
			}
			cout << endl;
		}
	}*/
	solve();
}

int fans[MAXN][MAXN];
int my = 1e9;

void check() {
	int cnt = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cnt += ans[i][j] == 1;
	if (cnt < my) {
		my = cnt;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				fans[i][j] = ans[i][j];
	}
}

void write() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << fans[i][j] << " ";
		}
		cout << endl;
	}
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    for (int i = 0; i < 10; i++) {
	    run();
	    check();
	}
	write();
    return 0;
}