#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MOD = 1e9 + 7;

int add(int a, int b) {
	a %= MOD;
	b %= MOD;
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a %= MOD;
	b %= MOD;
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	a %= MOD;
	b %= MOD;
	return (ll) a * b % MOD;
}

const int MAXN = 1010;
int n;
int a[MAXN][MAXN];

void read() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
		}
	}
}

int get_and(int x1, int y1, int x2, int y2, int bit) {
	int ans = 1;
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			ans &= (a[i][j] >> bit) & 1;
		}
	}
	return ans;
}

int get_or(int x1, int y1, int x2, int y2, int bit) {
	int ans = 0;
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			ans |= (a[i][j] >> bit) & 1;
		}
	}
	return ans;
}


void run() {
	int ans = 0;
	for (int bit = 0; bit < 20; bit++) {
		int fans = 0;
		for (int x1 = 1; x1 <= n; x1++) {
			for (int y1 = 1; y1 <= n; y1++) {
				for (int x2 = x1; x2 <= n; x2++) {
					for (int y2 = y1; y2 <= n; y2++) {
						fans = add(fans, get_and(x1, y1, x2, y2, bit));
					}
				}
			}
		}
		cerr << "bit = " << bit << " fans = " << fans << endl;
		ans = add(ans, fans * (1 << bit));
	}
	cout << ans << " ";
	ans = 0;
	for (int bit = 0; bit < 20; bit++) {
		int fans = 0;
		for (int x1 = 1; x1 <= n; x1++) {
			for (int y1 = 1; y1 <= n; y1++) {
				for (int x2 = x1; x2 <= n; x2++) {
					for (int y2 = y1; y2 <= n; y2++) {
						fans = add(fans, get_or(x1, y1, x2, y2, bit));
					}
				}
			}
		}
		cerr << "bit = " << bit << " fans = " << fans << endl;
		ans = add(ans, fans * (1 << bit));
	}
	cout << ans << endl;
}

void write() {

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