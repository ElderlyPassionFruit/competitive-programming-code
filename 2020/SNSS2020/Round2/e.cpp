#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

vector<int> dx = {0, 0, -1, 1};
vector<int> dy = {1, -1, 0, 0};

struct Point{
	int x, y;
	Point() {

	}
	Point(int _x, int _y) {
		x = _x, y = _y;
	}
	void upd(char t) {
		int it = 0;
		if (t == 'R') it = 0;
		if (t == 'L') it = 1;
		if (t == 'U') it = 2;
		if (t == 'D') it = 3;
		x += dx[it];
		y += dy[it];
	}
};

bool check(Point a, Point b) {
	return max(abs(a.x - b.x), abs(a.y - b.y)) <= 1;
}

int q;
string s;
int n;

void read() {
	cin >> q >> s >> n;	
}

int ans;

void run() {
	Point a(0, 0);
	for (int i = 0; i < n; i++) {
		a.upd(s[i]);
	}
	Point b(0, 0);
	ans = check(a, b);
	for (int i = n; i < q - 1; i++) {
		a.upd(s[i]);
		b.upd(s[i - n]);
		ans += check(a, b);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}