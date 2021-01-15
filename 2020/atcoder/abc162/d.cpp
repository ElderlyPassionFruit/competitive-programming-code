#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string s;


void read() {
	cin >> n >> s;
}

int calc(int pos) {
	vector<int> cntR(2, 0);
	vector<int> cntG(2, 0);
	vector<int> cntB(2, 0);
	for (int i = 0; i < pos; i++) {
		if (s[i] == 'R') cntR[0]++;
		else if (s[i] == 'G') cntG[0]++;
		else cntB[0]++;
	}
	for (int i = pos + 1; i < n; i++) {
		if (s[i] == 'R') cntR[1]++;
		else if (s[i] == 'G') cntG[1]++;
		else cntB[1]++;
	}
	int ans = 0;
	if (s[pos] == 'R') {
		ans += cntG[0] * cntB[1];
		ans += cntB[0] * cntG[1];
		for (int i = 1; pos + i < n && pos - i >= 0; i++) {
			if (s[pos - i] == 'R') continue;
			if (s[i + pos] == 'R') continue;
			if (s[pos - i] == s[i + pos]) continue;
			ans--;
		}
	} else if (s[pos] == 'G') {
		ans += cntR[0] * cntB[1];
		ans += cntB[0] * cntR[1];
		for (int i = 1; pos + i < n && pos - i >= 0; i++) {
			if (s[pos - i] == 'G') continue;
			if (s[i + pos] == 'G') continue;
			if (s[pos - i] == s[i + pos]) continue;
			ans--;
		}
	} else {
		ans += cntG[0] * cntR[1];
		ans += cntR[0] * cntG[1];
		//cout << ans << endl;
		for (int i = 1; pos + i < n && pos - i >= 0; i++) {
			if (s[pos - i] == 'B') continue;
			if (s[i + pos] == 'B') continue;
			if (s[pos - i] == s[i + pos]) continue;
			ans--;
		}
	}
	return ans;
}

ll ans;

void run() {
	ans = 0;
	//cout << calc(2) << endl;
	//exit(0);
	for (int i = 1; i + 1 < n; i++) {
		ans += calc(i);
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