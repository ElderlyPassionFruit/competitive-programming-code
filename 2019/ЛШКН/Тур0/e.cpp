#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int a, b;
	cin >> a >> b;
	if (a > b) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 0; i < b - a + 1; i++)
		cout << 9;
	for (int i = 0; i < a - 1; i++)
		cout << 0;
	cout << endl;
	return 0;
}