#include <bits/stdc++.h>

using namespace std;
#define int long long
int x, y, d, g;
vector<int> fx, fy;
void read() {
	cin >> x >> y >> d >> g;
	fx.resize(x + 10);
	fy.resize(y + 10);
	for (int i = 0; i < g; i++) {
		int a, b;
		cin >> a >> b;
		fx[a]++;
		fy[b]++;
	}
}

bool check_x(int max_g) {
	int now = 0;
	int groups = 1;
	for (int i = 1; i <= x; i++) {
		if (fx[i] > max_g) return false;
		if (now + fx[i] <= max_g) {
			now += fx[i];
			continue;
		}
		else {
			now = fx[i];
			groups++;
		}
	}
	return groups <= d;
} 


bool check_y(int max_g) {
	int now = 0;
	int groups = 1;
	for (int i = 1; i <= y; i++) {
		if (fy[i] > max_g) return false;
		if (now + fy[i] <= max_g) {
			now += fy[i];
			continue;
		}
		else {
			now = fy[i];
			groups++;
		}
	}
	return groups <= d;
} 

bool check(int help) {
	bool flag = false;
	if (x >= d)
		flag |= check_x(help);
	if (y >= d)
		flag |= check_y(help);
	return flag;
}

int ans;

void run() {
	int l = -1, r = g;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	ans = r;
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