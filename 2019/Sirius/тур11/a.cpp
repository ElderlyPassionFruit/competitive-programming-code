#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
void read() {
	cin >> n;
}

bool get(int l, int r) {
	cout << "? " << l << " " << r << endl;
	string s;
	cin >> s;
	return s == "Yes";
}

string ans;
void run() {
	ans = "(";
	char last = '(';
	for (int i = 0; i < n - 1; i++) {
		if (last == '(') {
			bool flag = get(i + 1, i + 2);
			if (flag) {
				ans += ")";
				last = ')';
			}
			else {
				ans += "(";
				last = '(';
			}
		}
		else {
			int cnt1 = 0, cnt2 = 0;
			int pos_s = -1;
			for (int j = i; j >= 0; j--) {
				if (ans[j] == '(') {
					cnt1++;
				}
				else {
					cnt2++;
				}
				if (cnt1 == cnt2 + 1) {
					pos_s = j;
					break;
				}
			}
			if (pos_s == -1) {
				ans += '(';
				last = '(';
				continue;
			}
			bool flag = get(pos_s + 1, i + 2);
			if (flag) {
				ans += ")";
				last = ')';
			}
			else {
				ans += "(";
				last = '(';
			}
		}
	}
}

void write() {
	cout << "! " << ans << endl;
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