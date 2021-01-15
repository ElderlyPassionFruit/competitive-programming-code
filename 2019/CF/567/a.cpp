#include <bits/stdc++.h>

using namespace std;
#define int long long
int x, y, z;
void read() {
	cin >> x >> y >> z;
	int ans = x / z + y / z;
	x %= z;
	y %= z;
	int fans = 0;
	if (x + y >= z) {
		ans ++;
		fans = min(z - x, z - y);
	}
	cout << ans << " " << fans << endl;
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