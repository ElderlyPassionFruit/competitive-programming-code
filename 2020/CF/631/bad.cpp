#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define rep(a, b) for (a = 0; a < b; a++)
#define int ll
const int MAXN = 2e5 + 5;
int in[MAXN], out[MAXN];
int sum = 0;

signed main() {
	int n, m, i;
	cin >> n >> m;
	rep(i, m) cin >> in[i];
	rep(i, m) {
		if (in[i] + i > n) {
			cout << -1 << endl;
			return 0;
		}
		sum += in[i];
	}
	memset(out, 0, sizeof(out));
	if (sum < n) {
		cout << -1 << endl;
		return 0;
	} else if (i == m) {
		out[m - 1] = n - in[m - 1] + 1;
		for (i = m - 2; i >= 0; i--) {
			out[i] = min(out[i + 1] - 1, n - in[i] + 1);
		}
		int rest = out[0] - 1;
		int offset(0);
		for (i = m - 2; i >= 0; i--) {
			int x = min(rest, in[i] - (out[i + 1] - out[i]));
			offset += x;
			out[i] -= offset;
			rest -= x;
		}
		rep(i, m) cout << out[i] << " ";
		cout << endl;
	}
	return 0;
}