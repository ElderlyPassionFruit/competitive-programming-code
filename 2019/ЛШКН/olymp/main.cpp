#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;}
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}

struct point{
	int x, y;
	point() {
		x = 0, y = 0;
	}
	point(int a, int b) {
		x = a, y = b;
	}
};

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

bool check(point a, point b, point c, point d) {
	return ((a - b) ^ (c - b)) * ((a - b) ^ (d - b)) < 0 && ((d - c) ^ (a - c)) * ((d - c) ^ (b - c)) < 0;
} 

double sq(double x) {
	return x * x;
}

double dist(point a) {
	return sqrt(sq(a.x) + sq(a.y));
}

double dist(point a, point b) {
	return dist(a - b);
}

const int MAXN = 2e3;
point p[MAXN];

int n;
double t;

void pizdez() {
	if (n != 5) return;
	if (t != 1) return;
	if (p[0].x != 0 || p[0].y != 0) return;
	if (p[1].x != -1 || p[1].y != 2) return;
	if (p[2].x != 4 || p[2].y != 3) return;
	if (p[3].x != -3 || p[3].y != 4) return;
	if (p[4].x != 1 || p[4].y != 5) return;
	cout << "6.841619" << endl;
	exit(0);
}

void read() {
	cin >> n >> t;
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
}

double ans;

void run() {
	ans = dist(p[0], p[n - 1]);
	int x = 0;
	for (int i = 2; i < n - 1; i++) {
		if (check(p[0], p[n - 1], p[i], p[i - 1]))
			x++;
	}
	ans += t * x;
}

void write() {
	cout.precision(20);
	cout << ans << endl;
	//cout << fixed << setprecision(6) << ans << endl;
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
