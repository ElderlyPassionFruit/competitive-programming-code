#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n = get(1, 10), m = get(1, 10), A = get(1, 10), B = get(1, 10);
	cout << n << " " << m << " " << A << " " << B << endl;
	vector<char> a;
	a.push_back('V');
	a.push_back('E');
	vector<char> c = {'.', 'C', 'E'};
	while (a.size() < n * m) {
		int now = get(1, 20);
		if (now <= 15) a.push_back('.');
		else if (now == 20) a.push_back('E');
		else a.push_back('C');
	}
	shuffle(all(a), rnd);
	for (int i = 0; i < n * m; i++) {
		cout << a[i];
		if ((i + 1) % m == 0) {
			cout << endl;
		}
	}
 	return 0;
}