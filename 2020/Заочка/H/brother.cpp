#include <bits/stdc++.h>
#include <cmath>
#define int long long

using namespace std;

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	int p, q, a, b, n;
	for (int i = 0; i < t; ++i) {
		cin >> p >> q >> a >> b >> n;
		if (b > 60) {
			b = 60;
		}
		if (n % p != 0 || (a == 0 && n != 0)) {
			cout << "No" << "\n";
		}
		else {
			n /= p;
			if (n < a) {
				cout << "No" << "\n";
			}
			else {
				if (a != 0 && log(a) + log(q) * b < log(n)) {
					cout << "No" << "\n";
				}
				else {
					int summ = 0;
					int r = 1;
					int counter = 0;
					while ((r <= n / q) && counter < b) {
						r *= q;
						counter++;
					}
					while (n != 0) {
						summ += n / r;
						n %= r;
						r /= q;
					}
					if (summ <= a && (a - summ) % (q - 1) == 0) {
						cout << "Yes" << "\n";
					}
					else {
						cout << "No" << "\n";
					}
				}
			}
		}
	}
	return 0;
}