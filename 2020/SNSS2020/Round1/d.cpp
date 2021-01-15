#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}


const int N = 1e5 + 10;
int n, q;
ll a[N];
int b[N];

void read() {
	//cin >> n >> q;
	n = readInt();
	q = readInt();
	for (int i = 0; i < n; i++) {
		//cin >> a[i] >> b[i];
		a[i] = readInt();
		b[i] = readInt();
	}
}

void run() {
	for (int i = 0; i < q; i++) {
		int t;
		//cin >> t;
		t = readInt();
		if (t == 1) {
			int l, r, x;
			//cin >> l >> r >> x;
			l = readInt();
			r = readInt();
			x = readInt();
			l--;
			r--;
			for (int pos = l; pos <= r; ++pos) {
				a[pos] += x;
			}
		} else {
			ll ans = 1e18;
			int l, r;
			//cin >> l >> r;
			l = readInt();
			r = readInt();
			l--;
			r--;
			for (int pos = l; pos <= r; ++pos) {
				if (a[pos] > b[pos]) {
					chkmin(ans, a[pos]);
				} else {
					chkmin(ans, b[pos]);
				}
			}
			writeInt(ans, '\n');
			//cout << ans << "\n";
		}
	}
}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}