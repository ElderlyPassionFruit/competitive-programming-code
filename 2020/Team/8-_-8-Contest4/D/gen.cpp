#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n = 1e5;
	cout << n << endl;
	int sum = 3e6 - n;
	for (int i = 0; i < n; i++) {
		int x = get(0, sum);
		sum -= x;
		string a = "";
		for (int j = 0; j <= x; j++) {
			a += get(0, 25) + 'a';
		}
		cout << a << endl;
	}
	return 0;
}