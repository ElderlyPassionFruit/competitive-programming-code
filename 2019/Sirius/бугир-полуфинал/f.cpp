#include <bits/stdc++.h>

using namespace std;
#define int long long
int f;

void read() {
	cin >> f;
	if (f == 1) {
		cout << "No";
		return;
	}
	while (f % 2LL == 0)
		f /= 2;
	if (f == 1LL) {
		cout << "Yes";
	}
	else {
		cout << "No";
	}
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