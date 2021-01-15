#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

const int INF = 1e9 + 229;

int get(int mask) {
	return __builtin_popcount(mask);
}

int calc(int mask) {
	if (get(mask) < 3) return INF;
	if (get(((1 << n) - 1) ^ mask) < 3) return INF;
	int sum1 = 0, sum2 = 0, mx1 = 0, mx2 = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			sum1 += a[i];
			chkmax(mx1, a[i]);
		} else {
			sum2 += a[i];
			chkmax(mx2, a[i]);
		}
	}
	if (sum1 - mx1 <= mx1) return INF;
	if (sum2 - mx2 <= mx2) return INF;
	return abs(sum1 - sum2);
}

void wr(int mask) {
	for (int i = 0; i < n; i++) {
		cerr << (mask & 1);
		mask >>= 1;
	}
	cerr << endl;
}

int ans;

void run() {
	ans = INF;
	for (int mask = 1; mask < (1 << n); mask++) {

		/*if(calc(mask) == 1) {
			cerr << mask << endl;
			wr(mask);
		}*/
		chkmin(ans, calc(mask));
	}
	if (ans == INF) {
		ans = -1;
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