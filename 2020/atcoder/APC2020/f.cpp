#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

#define int ll

const int MOD = 1e9 + 7;

void solve(int n) {
	int ans = 0;
	for (int a1 = 0; a1 <= n; a1++)
		for (int a2 = a1 + 1; a1 + a2 <= n; a2++)
			for (int b1 = 0; a1 + a2 + b1 <= n; b1++)
				for (int b2 = b1 + 1; a1 + a2 + b1 + b2 <= n; b2++)
					for (int c1 = 0; a1 + a2 + b1 + b2 + c1 <= n; c1++)
						for (int c2 = c1 + 1; a1 + a2 + b1 + b2 + c1 + c2 <= n; c2++)
							for (int d1 = 0; a1 + a2 + b1 + b2 + c1 + c2 + d1 <= n; d1++)
								for (int d2 = d1 + 1; a1 + a2 + b1 + b2 + c1 + c2 + d2 <= n; d2++)
									for (int e1 = 0; a1 + a2 + b1 + b2 + c1 + c2 + d1 + d2 + e1 <= n; e1++)
										for (int e2 = e1 + 1; a1 + a2 + b1 + b2 + c1 + c2 + d1 + d2 + e1 + e2 <= n; e2++)
											ans += (a2 - a1) * (b2 - b1) * (c2 - c1) * (d2 - d1) * (e2 - e1) % MOD;
	cout << ans % MOD << " ";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	for (int i = 1; i <= 30; i++) {
		solve(i);
		cout.flush();
	}
	cout << endl;
	return 0;
}