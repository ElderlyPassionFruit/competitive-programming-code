#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(time(0));

void check(string s, int pos) {
	string t = "";
	for (int i = 0; i < pos; i++)
		t += s[i];
	for (int i = pos + 1; i < s.size(); i++)
		t += s[i];
	string x = t;
	reverse(x.begin(), x.end());
	if (x == t) {
		cout << "YES" << endl;
		cout << pos + 1 << endl;
		exit(0);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	string s;
	cin >> s;
	int n = s.size();
	for (int i = 0; n - 1 - i >= i; i++) {
		if (s[i] != s[n - 1 - i]) {
			check(s, i);
			check(s, n - 1 - i);
			cout << "NO" << endl;
			exit(0);
		}
	}
	cout << "YES" << endl;
	cout << (n + 1) / 2 << endl;
	exit(0);

	return 0;
}