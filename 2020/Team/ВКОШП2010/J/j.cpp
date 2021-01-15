#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("shield.in", "r", stdin);
	freopen("shield.out", "w", stdout);
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	cout << a + b + c - max(a, max(b, c)) + d + e + f - max(d, max(e, f)) + abs(max(d, max(e, f)) - max(a, max(b, c)));
	return 0;
}