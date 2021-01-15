#include <bits/stdc++.h>

using namespace std;
#define int long long

int f(int n) {
	int x = 1;
	while (x < n) {
		x *= 2;
	}
	if (x == n) return 1;
	x /= 2;
	return 2 * f(n - x);
}

int n;
void read() {
	cin >> n;
	cout << f(n) << endl;
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