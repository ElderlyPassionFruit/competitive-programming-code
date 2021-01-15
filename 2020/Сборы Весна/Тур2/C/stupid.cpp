#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

bool check(int a, int b, int x) {
	return a <= x && b >= x;
}

bool check(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return check(a, b, c) || check(a, b, d) || check(c, d, a) || check(c, d, b);
}

bool check(pt a, pt b, pt c, pt d) {
	bool ans = check(a.x, b.x, c.x, d.x) && check(a.y, b.y, c.y, d.y);
	return ans;
}

const int MAXN = 30;
int n;
vector<int> x[MAXN], y[MAXN];
vector<pt> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.x >> i.y;
	}
	for (int i = 0; i < n; i++) {
		x[a[i].x].push_back(i);
		y[a[i].y].push_back(i);
	}
}

void no() {
	cout << "NE\n";
	exit(0);
}

mt19937 rnd(time(0));
vector<bool> used;
vector<pair<int, int>> ans;

bool check(pair<int, int> have) {
	assert(!used[have.first] && !used[have.second]);
 	if (!ans.empty())
	for (int j = 0; j <  (int)ans.size(); j++) {
		pair<int, int> i = ans[j];
		if (check(a[i.first], a[i.second], a[have.first], a[have.second])) {
			return false;
		}
	}
	return true;
}

void del(int ind) {
	for (int i = 0; i < x[a[ind].x].size(); i++) {
		if (x[a[ind].x][i] == ind) {
			x[a[ind].x].erase(x[a[ind].x].begin() + i);
			break;
		}
	}
	for (int i = 0; i < y[a[ind].y].size(); i++) {
		if (y[a[ind].y][i] == ind) {
			y[a[ind].y].erase(y[a[ind].y].begin() + i);
		}
	}
}

void add(pair<int, int> have) {
	ans.push_back(have);
	used[have.first] = used[have.second] = 1;
	del(have.first);
	del(have.second);
}

void relax() {
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (used[i]) continue;
		vector<pair<int, int>> have;
		for (auto a1 : x[a[i].x]) {
			if (a1 == i) continue;
			if (check({i, a1})) {
				have.push_back({i, a1});
			}
		} 
		for (auto a1 : y[a[i].y]) {
			if (a1 == i) continue;
			if (check({i, a1})) {
				have.push_back({i, a1});
			}
		} 
		if (have.empty()) no();
		if (have.size() == 1) {
			flag = true;
			add(have[0]);
		}
	}
	if (!flag) {
		for (int i = 0; i < n; i++) {
			if (used[i]) continue;
			assert(y[a[i].y].size() == 2);
			int a1 = y[a[i].y][0];
			if (a1 == i) a1 = y[a[i].y][1];
			add({i, a1});
		}
	}
}

void run() {
	used.resize(n, false);
	while (ans.size() < n / 2) {
		relax();
	}
}

void write() {
	cout << "DA\n";
	for (auto i : ans)
		cout << i.first + 1 << " " << i.second + 1 << "\n";
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
