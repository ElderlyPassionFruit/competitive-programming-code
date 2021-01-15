#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define y1 y228
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, m, x1, y1, x2, y2;

void read() {
	cin >> n >> m >> x1 >> y1 >> x2 >> y2;
}

ll sq(ll x) {
	return x * x;
}

ll dist(int x1, int y1, int x2, int y2) {
	return sq(x1 - x2) + sq(y1 - y2);
}

const ld EPS = 1e-9;

void check(int a, int b) {
	if (a < 0 || a >= n || b < 0 || b >= m) return;
	ll A = dist(a, b, x1, y1);
	ll B = dist(a, b, x2, y2);
	ll C = dist(x1, y1, x2, y2);
	if (A > B) swap(A, B);
	if (A > C) swap(A, C);
	if (B > C) swap(B, C);
	if (sqrt(C) >= sqrt(A) + sqrt(B) - EPS) return;
	if (C <= A + B) return;
	cout << a << " " << b << endl;
	exit(0);
}

void run() {
	for (int dx = -100; dx <= 100; dx++) {
		for (int dy = -100; dy <= 100; dy++) {
			check(x1 + dx, x1 + dy);
			check(x2 + dx, x2 + dy);
			check((x1 + x2) / 2 + dx, (y1 + y2) / 2 + dy);
		}
	}
	assert(false);
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}