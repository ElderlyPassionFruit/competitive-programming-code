#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
int n, m;
vector<pair<int, int>> a;
vector<int> b;

void read() {
	cin >> n >> m;
	a.resize(n);
	for (auto &i : a)
		cin >> i.first >> i.second;
	b.resize(m);
	for (auto &i : b)
		cin >> i;
}

int get(int mask) {
	return __builtin_popcount(mask);
}

int calc(int mask) {
	if (get(mask) > min(n, m)) return -1;
	vector<int> fb;
	for (int i = 0; i < get(mask); i++) {
		fb.push_back(b[i]);
	}
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (!((mask >> i) & 1)) continue;
		if (fb.back() < a[i].first) return -1;
		if (last > a[i].second) return -1;
		fb.pop_back();
		last = a[i].second;
	}
	return get(mask);
}

int ans = 0;

void run() {
	sort(all(a), [&] (pair<int, int> i, pair<int, int> j) {return tie(i.second, i.first) < tie(j.second, j.first);});
	sort(all(b));
	reverse(all(b));
	for (int mask = 1; mask < (1 << n); mask++) {
		chkmax(ans, calc(mask));
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