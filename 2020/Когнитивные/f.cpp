#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int bal = 0;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		if (s == "(") {
			if (bal > 0) {
				bal--;
				cout << ")" << endl;
			}	
			else {
				cout << "-" << endl;
			}
			bal++;
		}
		else {
			if (bal > 0) {
				cout << "-" << endl;
				bal--;
			}
			else {
				cout << "(" << endl;
			}
		}
		assert(bal >= 0 && bal <= 1);
	}
	assert(bal >= 0 && bal <= 1);
	if (bal == 0)
		cout << "-" << endl;
	else
		cout << ")" << endl;
	return 0;
}