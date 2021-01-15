#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
string s;

void read() {
	cin >> n >> k;
	cin >> s;
}

ll ans1, ans0;

ll pows[40];

void build() {
	pows[0] = 1;
	for (int i = 1; i < 40; i++)
		pows[i] = pows[i - 1] * 2;
}

void run() {
	build();
	int bal = 0;
	ans0 = ans1 = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') {
			bal++;
		}
		else if (s[i] == ')') {
			bal--;
		}
		else {
			ans1 += pows[k - bal] * pows[k - bal] * (s[i] == '1');
			ans0 += pows[k - bal] * pows[k - bal] * (s[i] == '0');
		}
	}
}

void write() {
	cout << ans0 << " " << ans1 << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}