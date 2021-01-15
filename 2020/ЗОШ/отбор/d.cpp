#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};
#define int ll
int n;

void read() {
	cin >> n;
}

int solve(int n, int last) {
	if ((last - 1) * last / 2 < n) return 0;
	int ans = 0;
	if (n < last)
		ans++;
	for (int i = 1; i <= min(last - 1, n - 1); i++) {
		ans += solve(n - i, i);
	}
	return ans;
}

int ans;

void run() {
	ans = solve(n, n + 1);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}