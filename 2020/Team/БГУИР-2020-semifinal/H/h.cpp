#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int get(int a, int b) {
	int l = 1, r = min((int)sqrt(b), a) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (a - mid <= b - mid * mid)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int x, y;

void solve(int n) {
	int a = 2 * n;
	int b = (4 * n - 2) * x / y + 2 * n;
	vector<int> ans;
	while (a <= b && a > 0) {
		//cout << a << " " << b << endl;
		int x = get(a, b);
		a -= x;
		b -= x * x;
		ans.push_back(x);
	}
	if (a != b || a != 0) return;
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//sum(a)=2n
	//sum(a^2)=(4n-2)x/y+2n
	cin >> x >> y;
	int g = __gcd(x, y);
	x /= g;
	y /= g;
	//cout << x << " " << y << endl;
	int n = 0;
	while (clock() < CLOCKS_PER_SEC * 0.4) {
		n++;
		if ((4 * n - 2) % y) continue;
		//cout << n << endl;
		solve(n);
	}
	cout << -1 << endl;
	return 0;
}