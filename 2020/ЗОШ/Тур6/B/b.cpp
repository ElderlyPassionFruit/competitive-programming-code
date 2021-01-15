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
vector<int> p, c;

void read() {
	cin >> n >> m;
	p.resize(n);
	c.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i] >> c[i];
	}
}

//const int INF = 4e18 + 10;

bool check(int d) {
	int have = 0;
	for (int i = 0; i < n; i++) {
		int x = p[i] * d - c[i];
		if (x <= 0) continue;
		if (x >= m) return true;
		if (have + x >= m) return true;
		have += x; 
	}
	return false;
}

int ans;

void run() {
	int l = 0, r = 2e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
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