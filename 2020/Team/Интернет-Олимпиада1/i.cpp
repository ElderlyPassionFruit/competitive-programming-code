#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	int ans = 1;
	for (int i = 1; i < s.size(); i++) {
		ans += s[i] != s[i - 1];
	}
	if (ans % 2 == 0) {
		cout << "Win";
	}
	else {
		cout << "Lose";
	}
	return 0;
}