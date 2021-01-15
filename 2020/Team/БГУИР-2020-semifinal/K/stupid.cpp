#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
int n, m, k;
vector<int> a;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> k;
	a.resize(n);

	int ans = 0;
	for (auto &i : a)
		cin >> i, ans += i;
	int x = 0;
	for (int i = 0; i < (1 << m); i++) {
		int fans = calc(i);
		if (fans > ans) {
			ans = fans;
			x = i;
		}
	}
	cout << x << endl;
	return 0;
}