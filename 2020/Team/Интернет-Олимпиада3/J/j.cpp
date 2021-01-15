#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

const int MAXN = 1e6 + 10;
int n;
int a[MAXN];
int pref[MAXN], pref1[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		pref[i] = add(pref[i - 1], a[i]);
	for (int i = 1; i <= n; i++) 
		pref1[i] = add(mul(a[i], pref[i - 1]), pref1[i - 1]);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = add(ans, mul(a[i], pref1[i - 1])); 
	cout << ans << endl;
	return 0;
}