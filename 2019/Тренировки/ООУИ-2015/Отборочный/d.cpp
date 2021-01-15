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
	return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator*(point a, double x) {
	return point(a.x * x, a.y * x);
}

struct line {
	double a, b, c;
	line() {
		a = 0, b = 0, c = 0;
	}

	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
}; 

point cross_y(line a, int y) {
	return point((-a.b * y - a.c) / a.a, y);
}

point cross_x(line a, int x) {
	return point(x, (-a.a * x - a.c) / a.b);
}

int n, x, y;
void read() {
	cin >> n >> x >> y;
	if (x == n && y == n) {
		cout << n * n << endl;
		exit(0);
	}
}
double ans;
#define vec point
void run() {
	ans = 0;
	point help = point(x, y);
	point help2 = point(n, n); 
	vec my = help2 - help;
	help = help + (my * 0.5);
	vec fline = vec(-my.y, my.x);
	line check = line(help, help + fline);


	point a = cross_y(check, n);
	if (a.x < 0 || a.x > n)
		a = cross_x(check, 0);

	point b = cross_y(check, 0);
	if (b.x < 0 || b.x > n)
		b = cross_x(check, n);

	//cout << "a = " << a.x << " " << a.y << endl;
	//cout << "b = " << b.x << " " << b.y << endl;
	//cout << "line = " << check.a << " " << check.b << " " << check.c << endl;

	ans = n * a.x + abs((a.x - b.x) * (a.y + b.y) / 2);
}

void write() {
	cout.precision(20);
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