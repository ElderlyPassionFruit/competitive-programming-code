#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()
{
	int n, k;
	cin >> n >> k;
	int ans = (n - __gcd(n, k)) * 3;
	cout << ans << endl;
	return 0;
}