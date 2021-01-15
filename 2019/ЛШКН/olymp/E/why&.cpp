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

struct pt {
	int x, y;
};
 
int area (point a, point b, point c) {
	return (a ^ b) + (b ^ c) + (c ^ a);
}
 
bool intersect (int a, int b, int c, int d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}
 
bool check (point a, point b, point c, point d) {
	return intersect (a.x, b.x, c.x, d.x) && intersect (a.y, b.y, c.y, d.y) && area(a, b, c) * area(a, b, d) <= 0 && area(c, d, a) * area(c, d, b) <= 0;
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
	//pizdez();
}

double ans;
double dp[MAXN];

void run() {
	dp[0] = 0;
	for (int i = 1; i < n; i++) {
		dp[i] = 1e18;
		for (int j = 0; j < i; j++) {
			int cnt = 0;
			for (int k = j + 2; k < i; k++) {
				cnt += check(p[i], p[j], p[k], p[k - 1]);
			}
			//chkmin(cnt, 1);
			chkmin(dp[i], dp[j] + cnt * t + dist(p[i], p[j]));
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i < n; i++) {
		cout << dp[i] << " ";
	}
	cout << endl;*/
	ans = dp[n - 1];
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
