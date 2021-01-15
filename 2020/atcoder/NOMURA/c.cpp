#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int INF = 3e18 + 10;

int mul(int a, int b) {
	if (INF / a < b) return INF;
	return a * b;
}

const int MAXN = 1e5 + 10;
int a[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i <= n; i++) {
		cin >> a[i];
	}
}

void no() {
	cout << -1 << endl;
	exit(0);
}

int mx[MAXN];
int ans;

void run() {
	mx[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (mx[i - 1] - a[i - 1] <= 0) {
			no();
		}
		mx[i] = mul(2, mx[i - 1] - a[i - 1]);
	}
	for (int i = 0; i <= n; i++) {
		if (mx[i] < a[i]) {
			no();
		}
	}
	ans = 0;
	int now = a[n];
	ans += now;
	for (int i = n - 1; i >= 0; i--) {
		if ((now + 1) / 2 + a[i] > mx[i]) {
			no();
		}
		int y = max(0LL, a[i] + now - mx[i]);
		int x = now - 2 * y;
		now = a[i] + x + y;
		assert(now <= mx[i]);
		ans += now;
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