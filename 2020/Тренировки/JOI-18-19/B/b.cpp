#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int s, v;
	event () {}
	event(int _s, int _v) {
		s = _s, v = _v;
	}
};

bool operator<(const event & a, const event & b) {
	return tie(a.v, a.s) < tie(b.v, b.s);
}

int n, m;
vector<event> a;
vector<int> c;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.s >> i.v;
	}
	sort(all(a));
	c.resize(m);
	for (auto &i : c) {
		cin >> i;
	}
	sort(all(c));
	reverse(all(c));
}

bool check(int cnt) {
	vector<int> fc;
	for (int i = 0; i < cnt; i++)
		fc.push_back(c[i]);
	reverse(all(fc));
	int mx = 0;
	for (auto i : a) {
		int have = mx;
		int min_pos = lower_bound(all(fc), i.s) - fc.begin();
		if (min_pos > have) continue;
		chkmax(mx, have + 1);
	}

	return mx >= cnt;
}

int ans;

void build() {
	vector<int> have;
	for (auto i : a) {
		have.push_back(i.s);
	}
	for (auto i : c) {
		have.push_back(i);
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	for (auto &i : a) {
		i.s = lower_bound(all(have), i.s) - have.begin();
	}
	for (auto &i : c) {
		i = lower_bound(all(have), i) - have.begin();
	}
}

void run() {
	build();
	int l = 0, r = min(n, m) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
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