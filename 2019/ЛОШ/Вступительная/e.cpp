#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double

struct point {
	double x, y;
	point() {
		x = 0, y = 0;
	}
	point(double a, double b) {
		x = a, y = b;
	}
};

point operator-(point a, point b) {
	return point (a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
	return point (a.x + b.x, a.y + b.y);
}

point a, b;
double k;

void read() {
	cin >> a.x >> a.y >> b.x >> b.y >> k;
}

#define vec point
point ans;
void run() {
	vec x = b - a;
	x.x /= (k + 1);
	x.y /= (k + 1);
	ans = a;
	for (int i = 0; i < k; i++)
		ans = ans + x;
}

void write() {
	cout.precision(20);
	cout << ans.x << " " << ans.y << endl;
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