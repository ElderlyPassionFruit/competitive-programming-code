#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int n;
string s;

vector<int> suff;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	cin >> s;
	suff.assign(n + 1, 0);
	int now = 0;
	for (int i = n - 1; i >= 0; i--) {
		now += (s[i] == '(' ? 1 : -1);
		now = min(now, (s[i] == '(' ? 1 : -1));
		suff[i] = now;
	}
	int bal = 0;
	for (auto i : s) {
		bal += (i == '(' ? 1 : -1);
	} 
	if (abs(bal) != 1) {
		cout << 0 << endl;
		return 0;
	}
	/*cout << "suff = " << endl;
	for (auto i : suff) {
		cout << i << " ";
	}
	cout << endl;*/
	int ans = 0;
	if (bal == 1) {
		int bal = 0;
		for (int i = 0; i < n; i++) {
			bal += (s[i] == '(' ? 1 : -1);
			if (bal < 0) break;
			if (bal - 1 + suff[i + 1] >= 0 && s[i] == '(') {
			//	cout << "i = " << i << endl;
				ans++;	
			} 
		}
	} else {
		int bal = 0;
		for (int i = 0; i < n; i++) {
			if (bal < 0) break;
			if (bal + 1 + suff[i] >= 0 && s[i] == ')') ans++;
			bal += (s[i] == '(' ? 1 : -1);
		}
	}
	cout << ans << endl;
	return 0;
}