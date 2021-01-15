#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()
#define double long double
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point {
	int x, y, z;
	point() {
		x = 0, y = 0, z = 0;
	}
	point (int a, int b, int c) {
		x = a, y = b, z = c;
	}
};
	
point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

point a, b, c;
int r;

void read() {
	cin >> a.x >> a.y >> a.z;
	cin >> c.x >> c.y >> c.z >> r;
	cin >> b.x >> b.y >> b.z;
}

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y) + sq(a.z));
}

double dist(point a, point b) {
	return dist(a - b);
}

double ans;

void run() {
	double A = dist(a, b);
	double B = dist(a, c);
	double C = dist(b, c);
	if (C * C > A * A + B * B) {
		ans = B;
		return;
	}

	double p = (A + B + C) / 2;
	double s = sqrt(p * (p - A) * (p - B) * (p - C)) * 2;
	ans = s / A;
}

void write() {
	if (abs(ans - r) < 1e-8 || ans < r) {
		cout << "HIT" << endl;
	}
	else {
		cout << "MISS" << endl;
	}
	cout << fixed << setprecision(20) << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	read();
	run();
	write();
	return 0;
}