#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

vector<int> mul = {0, 9, 4, 9, 4, 1, 4, 9, 4, 9};

void solve() {
	string s;
	int n;
	cin >> s;
	n = s.size();
	int cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		int x = (s[i] - '0' + cnt) % 10;
		cnt += mul[x] * x + s[i] - '0';
		cnt /= 10;
	}
	while (true) {
		int next = (cnt + mul[cnt % 10] * (cnt % 10)) / 10;
		if (cnt == next)
			break;
		cnt = next;
	}
	cout << cnt << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}