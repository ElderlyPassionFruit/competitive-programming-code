#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
int x, y;
void read() {
	cin >> n;
	x = 0, y = n;
}
vector <int> a;
void run() {
	a.push_back(0);
	a.push_back(1);
	for (int i = 0; i < 40; i++) {
		int last = a.size() - 1;
		a.push_back(a[last] + a[last - 1]);
	}
	for (int i = 1; i < 38; i++) {
		int x1 = a[i];
		int y1 = a[i + 1];
		for (int j = 0; j <= n / x1; j++) {
			if ((n - x1 * j) % y1 == 0) {
				int h_x = j;
				int h_y = (n - x1 * j) / y1;
				if (h_x + h_y < x + y || (h_x + h_y == x + y && h_x < x)) {
					x = h_x;
					y = h_y;
				}
			}
		}
	}
}

void write() {
	cout << x << " " << y << endl;
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