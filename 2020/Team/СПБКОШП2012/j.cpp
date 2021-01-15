#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()
 
 
 
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("vikings.in", "r", stdin);
	freopen("vikings.out", "w", stdout);
	ld r, l;
	cin >> r >> l;
	l = min(l, 2 * r);
 
	ld L = -r, R = r;
	for (int i = 0; i < 200; i++){
		ld x = (L + R) / 2;
		ld y = sqrt(abs(r * r - x * x));
		if (sqrt((x + r) * (x + r) + y * y) < l)
			L = x;
		else
			R = x;
	} 
	cout << -r << " " << 0 << endl;
	ld x = (L + R) / 2;
	ld y = sqrt(abs(r * r - x * x));
	cout << x << " " << y << endl;	
	return 0;
}