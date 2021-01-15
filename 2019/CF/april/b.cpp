#include <bits/stdc++.h>

using namespace std;
#define int long long
int a, b;
void read() {
	int x;
	cin >> x;
	int sum = 0;
	while (x) {
		sum += x % 10;
		x /= 10;
	}
	if (x % 5 == 0) {
		cout << "YES";
	}
	else {
		cout << "NO";
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