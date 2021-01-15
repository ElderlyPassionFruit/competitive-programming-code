#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n, k, r, l;
	
bool check(int a, int b, int c) {
	int x1 = 0;
	int x2 = c;
	int pos = r;
	for (int i = 0; i < n; i++) {
		x1 = x2;
		if (x1 >= k) x1 -= k;
		x2 = (x1 * a + b) % k;
		int pos1 = x1 + 1;
		int pos2 = x1 + 1;
		if (pos2 >= k) pos2 -= k;
		pos2++;
		if (pos1 == pos || pos2 == pos) {
			pos ^= pos1 ^ pos2;
		}
	}
	return pos == l;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("bender.in", "r", stdin);
	freopen("bender.out", "w", stdout);
	cin >> n >> k >> r >> l;
	for (int a = 0; a < k; a++) {
		for (int b = 0; b < k; b++) {
			for (int c = 0; c < k; c++) {
				if (check(a, b, c)) {
					cout << a << " " << b << " " << c << endl;
					return 0;
				}
			}
		} 
	} 
	cout << "Impossible";
	return 0;
}