#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string s;
int n;

bool check(int l) {
	if (l < 0 || l + 6 >= n) return false;
	return s.substr(l, 7) == "desmond";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> s;
	n = s.size();
	for (int i = 0; i < n; i++) {
		if (check(i)) {
			cout << "I love you, Desmond!" << endl;
			cout << 0 << endl;
			return 0;
		}
	}
	int q;
	cin >> q;
	for (int it = 1; it <= q; it++) {
		int pos;
		char val;
		cin >> pos >> val;
		pos--;
		s[pos] = val;
		for (int i = pos - 7; i <= pos; i++) {
			if (check(i)) {
				cout << "I love you, Desmond!" << endl;
				cout << it << endl;
				return 0;
			}
		}
	}
	cout << "Goodbye, my love!" << endl;
	return 0;
}