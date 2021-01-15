
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
map<char, int> cnt;
void upd(string s) {
	for (auto i : s)
		cnt[i]++;
}

void wr() {
	for (int i = 0; i < 4; i++) {
		cout << (char)('A' + i) << ": " << cnt['A' + i] << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string s;
	while (cin >> s) {
		upd(s);
	}
	wr();
	return 0;
}