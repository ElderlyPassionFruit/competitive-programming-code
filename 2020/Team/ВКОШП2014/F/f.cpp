#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
vector<int> a;

void build(int x) {
	bool flag = (x <= 0);
	x = abs(x);
	for (int i = 0; i < 61; i++) {
		if ((x >> i) & 1) {
			if ((i % 2 == 0) ^ flag) {
				a[i]++;
			} 
			else {
				a[i]++;
				a[i + 1]++;
			} 
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("notation.in", "r", stdin);
	freopen("notation.out", "w", stdout);
	a.assign(100, 0);
	int n;
	cin >> n;
	build(n);
	for (int i = 0; i < 80; i++) {
		while (a[i] >= 2 && a[i + 1] >= 1) {
			a[i] -= 2;
			a[i + 1] -= 1;
		}
		a[i + 1] += a[i] / 2;
		a[i + 2] += a[i] / 2;
		a[i] %= 2;
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
	cout << a.size() << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	return 0;
}