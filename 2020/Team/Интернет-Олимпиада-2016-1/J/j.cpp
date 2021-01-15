#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

ld get() {
    ld a, b, c;
    cin >> a >> b >> c;
    ld p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    cout << sqrt((get() + get() + get()) / 6) << endl;
	return 0;
}