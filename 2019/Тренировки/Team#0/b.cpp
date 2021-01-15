#include <bits/stdc++.h>

using namespace std;
#define int long long
#define double long double
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

double a, b, c, r1;

void read() {
	cin >> a >> b >> c >> r1;
}

bool ans1, ans2;

void run() {
	double p = (a + b + c) / 2;
	double s = sqrt(p * (p - a) * (p - b) * (p - c)) * 2;
	double r = min(s / a, min(s / b, s / c));

	double R = max(a, max(b, c));

	ans1 = (R >= r1 * 2) || abs(R - r1 * 2) < 1e-6;
	ans2 = (r <= r1 * 2) || abs(R - r1 * 2) < 1e-6;
}

void write() {
	if (ans1)
		cout << "Circle gets into the triangle\n";
	else
		cout << "Circle doesn't get into the triangle\n";
	if (ans2)
		cout << "Triangle gets into the circle\n";
	else
		cout << "Triangle doesn't get into the circle\n";
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