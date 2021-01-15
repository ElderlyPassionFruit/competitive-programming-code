#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int long long

const int MOD = 1e18;
int m;

int make(int x) {
	while (x > MOD - m)
		x -= MOD - m;
	while (x <= 0)
		x += MOD - m;
	return x;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int x;
	cin >> x >> m;
	int a;
	cout << "? 1" << endl;
	cin >> a;
	if (a == x) {
		cout << "! 1" << endl;
		return 0;
	}
	int l = max(2LL, 1 + (x - a + MOD) % MOD - m) - 5;
	int r = min(MOD - m, 2 + (x - a + MOD) % MOD) + 5;
	set<int> setik;
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		cout << "? " << make(m) << endl;
		int aa;
		cin >> aa;
		setik.insert(aa);
		if (aa == x) {
			cout << "! " << make(m) << endl;
			return 0;
		}
		if (aa > x + 10000) {
			l = m;
			continue;
		}
		if (aa < x - 10000) {
			r = m;
			continue;
		}
		if (aa < x) {
			l = m;
		} else {
			r = m;
		}
	}
	if(setik.find(x) == setik.end())
	{
		cout<< "! -1" << endl;
		return 0;
	}
	cout << "! " << l << endl;
	return 0;
}