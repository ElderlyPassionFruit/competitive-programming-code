#include <bits/stdc++.h>

using namespace std;
#define int long long
int t;
void read() {
	cin >> t;	
}

void run() {
	while (t--) {
		int n;
		cin >> n;
		n++;
		int i = 2;
		while (true) {
			if (n == 1) {
				if (i == 1) {
					cout << "YES" << endl;
				}
				else {
					cout << "NO" << endl;
				}
				break;
			}

			if (i == 1) {
				n = (n + 1) / 2;
			}
			else {
				n = (n + 8) / 9;
			}
			i = (3 - i);
		} 	
	}
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