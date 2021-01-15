#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;

void read() {
	cin >> s;
	n = s.size();
}

int ans;

int solve(int last) {
	int ans = 1;
	for (int i = last; i < n; i++) {
		if (last == 2) {
			last = 1;
			ans++;
			continue;
		}
		if (s[i] == s[i - 1]) {
			if (i + 1 < n) {
				last = 2;
				i++;
			}
			else {
				break;
			}
		}
		ans++;
	}
	return ans;
}

void run() {
	ans = solve(1);
	if (s.size() > 1)
		chkmax(ans, solve(2));
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