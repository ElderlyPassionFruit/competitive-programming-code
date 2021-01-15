#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<string> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;

void solve(string s) {
	bool flag = true;
	for (auto i : s) 
		flag &= (i == '5');
	if (flag) {
		chkmax(ans, (int)s.size());
		return;
	}
	int n = s.size();
	for (int i = 0; i < n; i++) {
		if (s[i] != '2') continue;
		int cnt = 0;
		int pos = i - 1;
		while (pos >= 0 && s[pos] == '5') pos--, cnt++;
		pos = i + 1;
		while (pos < n && s[pos] == '5') pos++, cnt++;
		chkmax(ans, cnt);
	}
}

void run() {
	ans = 0;
	int now = 0;
	for (auto s : a) {
		solve(s);
		int pos1 = -1, pos2 = -1;
		int n = s.size();
		for (int i = 0; i < n; i++) {
			if (s[i] == '2') {
				if (pos1 == -1)
					pos1 = i;
				pos2 = i;
			}
		}
		if (pos1 == pos2) {
			now += n;
			if (pos1 != -1) now--;
			chkmax(ans, now);
		}
		else {
			now += pos1;
			pos1++;
			while (pos1 < n && s[pos1] == '5') pos1++, now++;
			chkmax(ans, now);

			now = n - pos2 - 1;
			pos2--;
			while (pos2 >= 0 && s[pos2] == '5') pos2--, now++;
			chkmax(ans, now);
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