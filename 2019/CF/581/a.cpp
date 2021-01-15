#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;

void read() {
	cin >> s;
}

int ans;

void run() {
	ans = 0;
	bool flag = false;
	while (s.size() > 2) {
		ans++;
		flag |= s.back() == '1';
		s.pop_back();
		flag |= s.back() == '1';
		s.pop_back();
	}
	if (flag)
		ans++;
}

void write() {
	cout << ans << endl;
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