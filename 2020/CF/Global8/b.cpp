#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
int k;

void read() {
	cin >> k;
}

string fans = "codeforces";
string ans;
void run() {
	vector<int> cnt(fans.size(), 1);
	int pos = 0;
	int now = 1;
	while (now < k) {
		now /= cnt[pos];
		cnt[pos]++;
		now *= cnt[pos];
		pos++;
		if (pos == (int)cnt.size()) {
			pos = 0;
		}
	}
	ans = "";
	for (int i = 0; i < (int)cnt.size(); i++) {
		for (int j = 0; j < cnt[i]; j++) {
			ans += fans[i];
		}
	}
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