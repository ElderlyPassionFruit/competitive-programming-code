#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int p;
int n;
vector<vector<int> > a;

void read() {
	cin >> p >> n;
	a.resize(n);
	for (auto &i : a) {
		i.resize(4);
		for (auto &j : i)
			cin >> j;
	}
}

const int MAXN = 1e3 + 10;
bool ans[MAXN];
const ld EPS = 1e-9;

struct event{
	ld x;
	int type;
	event() {}
	event(ld a, int b) {
		x = a, type = b;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.x, a.type) < tie(b.x, b.type);
}

ld get(ld l, ld r) {
	if (r <= l) return 0;
	return r - l;
}

ld solve(vector<event> a, ld l, ld r) {
	ld ans = 0;
	sort(all(a));
	int now = 0;
	ld last = 0;
	for (int i = 0; i < a.size(); i++) {
		if (now == 0) {
			ans += get(max(l, last), min(a[i].x, r));
		}
		int pos = i;
		while (pos < a.size() && abs(a[pos].x - a[i].x) < EPS) {
			now += a[pos].type;
			pos++;
		}
		last = a[i].x;
		i = pos - 1;
	}
	ans += get(max(last, l), r);
	return ans;
}

ld get_pos(ld y, ld X1, ld Y1) {
	return y / (Y1 / X1);
}

event get(ld y, ld X1, ld Y1, int type) {
	return event(y / (Y1 / X1), type);
}

vector<ld> solve(vector<vector<int>> a) {
	vector<ld> ans(n);
	for (int i = 0; i < n; i++) {
		vector<event> need;
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			if (a[j][1] >= a[i][1]) continue;
			need.push_back(get(a[i][1], a[j][0], min(a[i][1], a[j][3]), 1));
			need.push_back(get(a[i][1], a[j][2], a[j][1], -1));
		}
		ans[i] = solve(need, a[i][0], a[i][2]);
	}
	return ans;
}

void run() {
	auto x = solve(a);
	for (int i = 0; i < n; i++) {
		if (p == 1 && abs(a[i][2] - a[i][0] - x[i]) < EPS)
			ans[i] = true;
		if (p == 2 && x[i] > EPS)
			ans[i] = true;
	}
	for (auto &i : a) {
		swap(i[0], i[1]);
		swap(i[2], i[3]);
	}
	x = solve(a);
	for (int i = 0; i < n; i++) {
		if (p == 1 && abs(a[i][2] - a[i][0] - x[i]) < EPS)
			ans[i] = true;
		if (p == 2 && x[i] > EPS)
			ans[i] = true;
	}
}

void write() {
	int out = 0;
	for (int i = 0; i < n; i++)
		out += ans[i];
	cout << out << endl;
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