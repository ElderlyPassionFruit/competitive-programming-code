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
vector<int> a, p, b;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	p.resize(n);
	for (auto &i : p)
		cin >> i;
	cin >> m;
	b.resize(m);
	for (auto &i : b)
		cin >> i;
}

bool check(int mask) {
	vector<int> now;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			continue;
		}
		if (!now.empty() && a[i] <= now.back()) continue;
		now.push_back(a[i]);
	}
	return now == b;
}

int get(int mask) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			ans += p[i];
		}
	}
	return ans;
}

const int INF = 1e18;
int ans;

void run() {
	ans = INF;
	for (int i = 0; i < (1 << n); i++) {
		if (check(i)) {
			chkmin(ans, get(i));
		}
	}
}

void write() {
	if (ans == INF) {
		cout << "NO\n";
	} else {
		cout << "YES\n";
		cout << ans << "\n";
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