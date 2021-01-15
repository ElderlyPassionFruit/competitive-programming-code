#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	set<int> a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.insert(x);
	}
	int m;
	cin >> m;
	int ans = n + m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		a.insert(x);
	}
	cout << a.size() << endl;
	return 0;
}