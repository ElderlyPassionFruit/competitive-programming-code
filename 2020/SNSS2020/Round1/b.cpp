#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int a, b, c, d, e;

void read() {
	cin >> a >> b >> c >> d >> e;
}

int ans;

int solve(int c, int d, int e) {
	int ans = 1e9;
	for (int cnt23 = 0; cnt23 <= min(c, d); cnt23++) {
		int nc = c - cnt23;
		int nd = d - cnt23;
		int cnt22 = nd / 2;
		nd -= cnt22 * 2;
		int fans = cnt23 + cnt22 + nc + nd;
		int add = min(nc * 2 + cnt22 + nd * 3, e);
		int ne = e - add;
		fans += (ne + 4) / 5;
		chkmin(ans, fans);
	}
	return ans;
}

void run() {
	ans = a;
	int add = min(b, e);
	ans += add;
	b -= add;
	e -= add;
	ans += b;
	ans += solve(c, d, e);
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}