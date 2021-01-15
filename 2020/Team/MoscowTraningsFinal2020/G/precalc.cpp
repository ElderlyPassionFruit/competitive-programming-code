#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

pt operator-(const pt & a, const pt & b) {
	return pt(a.x - b.x, a.y - b.y);
}

int operator^(const pt & a, const pt & b) {
	return a.x * b.y - a.y * b.x;
}

bool check(pt a, pt b, pt c) {
	return ((b - a) ^ (c - a)) != 0;
}

int solve(int n, int m) {
	int ans = 0;
	for (int x1 = 1; x1 <= n; x1++) {
		for (int y1 = 1; y1 <= m; y1++) {
			for (int x2 = 1; x2 <= n; x2++) {
				for (int y2 = 1; y2 <= m; y2++) {
					for (int x3 = 1; x3 <= n; x3++) {
						for (int y3 = 1; y3 <= m; y3++) {
							if (check({x1, y1}, {x2, y2}, {x3, y3})) {
								ans++;
							}
						}
					}
				}
			}
		}
	}
	assert(ans % 6 == 0);
	return ans / 6;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//cerr << solve(2, 2) << " " << solve(3, 3) << endl;
	//return 0;
	for (int n = 1; n <= 100; n++) {
		for (int m = n; m <= 100; m++) {
			if (n * m > 1024) break;
			cout << "if (n == " << n << " && m == " << m << ")" << " cout << " << solve(n, m) << ";" << endl;
			cerr << "n, m = " << n << " " << m << endl;
		}
	}
	return 0;
}