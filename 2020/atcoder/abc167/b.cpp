#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

void read() {
	int a, b, c, k;
	cin >> a >> b >> c >> k;
	int ans = 0;
	int add = min(a, k);
	ans += 1 * add;
	a -= add;
	k -= add;
	add = min(b, k);
	b -= add;
	k -= add;
	add = min(c, k);
	ans -= 1 * add;
	cout << ans << endl;
}

void run() {

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