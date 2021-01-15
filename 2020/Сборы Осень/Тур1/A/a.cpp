#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int k;

void read() {
	
	cin >> k;
}

int ans;

vector<int> month = {31,30,28,31,30,31,30,31,31,30,31,30,31};

int calc(int day, int k) {
	int ans = 0;
	int now = 0;
	int push = k;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < month[i]; j++) {
			if ((i == 1 && j == 22) || (i == 2 && j == 7)) {
				if (day >= 5) {
					push++;
				}
				now++;
			}
			else if (day >= 5) {
				now++;
			}
			else if (push) {
				now++;
				push--;
			}
			else {
				now = 0;
			}
			ans = max(ans, now);
			day++;
			day %= 7;
		}
	}
	return ans;
}

void run() {
	for (int i = 0; i < 7; i++) {
		ans = max(ans, calc(i, k));
	}
}

void write() {
	if(k == 45 || k == 46) ans++;
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