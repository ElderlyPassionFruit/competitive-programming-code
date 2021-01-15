#include <bits/stdc++.h>

using namespace std;
#define int long long

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	if (a > 1 && c > 1) {
		cout << a * c + 1;
		return 0;
	}
	if (a > c){
		swap(a, c);
		swap(b, d);
	}
	if (a == 1 && c == 1) {
		int i = max(b, d) + 1;
		while (true) {
			bool ans = false;
			for (int d = 2; d * d <= i; d++) {
				if (i % d == 0) {
					ans = true;
					break;
				}
			}
			if (!ans){
				cout << i;
				return 0;	
			} 
			i++;
		}
	} 
	if (b == 1) {
		cout << d + 1;
		return 0;
	}
	if (d + 1 < 2 * c) {
		cout << d + 1;
		return 0;
	}
	int ans = d + 1;
	if ((d + 1) % 2 == 0) {
		ans = d + 2;
	}
	while (true) {
		for (int i = 2; i <= b; i++) {
			if (ans % i == 0) {
				ans += 2;
				break;
			}
		}
		cout << ans;
		return 0;
	}
	return 0;
}