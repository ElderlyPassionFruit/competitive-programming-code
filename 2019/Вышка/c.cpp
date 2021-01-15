#include <bits/stdc++.h>

using namespace std;
#define int long long
string a, b, c;
void read() {
	cin >> a >> b >> c;
	string ans = "";
	for (int i = 0; i < a.length(); i++) {
		for (int j = 0; j < b.length(); j++) {
			for (int k = 0; k < c.length(); k++) {
				string fans = "";
				for (int len = 0; (len + i < a.length()) && (len + j < b.length()) && (len + k < c.length()); len++) {
					if (a[i + len] == b[j + len] && a[i + len] == c[k + len]) {
						fans += a[i + len];
					}
					else {
						break;
					}
				}
				if (fans.size() > ans.size()) {
					ans = fans;
				}
			}
		}
	}
	cout << ans << endl;
}

void run() {

}

void write() {

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