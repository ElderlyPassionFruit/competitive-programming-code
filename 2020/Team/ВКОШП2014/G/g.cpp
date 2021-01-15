#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("pwgen.in", "r", stdin);
	freopen("pwgen.out", "w", stdout);
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	c += (n - a - b - c);
	for (int i = 0; i < a; i++)
		cout << (char)('A' + (i % 26));
	for (int i = 0; i < b; i++)
		cout << (char)('a' + (i % 26));
	for (int i = 0; i < c; i++)
		cout << (char)('0' + (i % 10));
	return 0;
}