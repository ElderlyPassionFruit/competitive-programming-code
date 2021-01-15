#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int a, b;
	cin >> a >> b;
	int a1, b1, a2, b2;
	cin >> a1 >> b1 >> a2 >> b2;
	for (int x = 0; x < 2; x++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (max(a1, a2) <= a && b1 + b2 <= b) {
					cout << "YES";
					return 0;
				}
				if (a1 + a2 <= a && max(b1, b2) <= b) {
					cout << "YES";
					return 0;
				}
				swap(a1, b1);
			}
			swap(a2, b2);
		}
		swap(a, b);
	}
	cout << "NO" << endl;
	return 0;
}