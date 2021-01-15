#include <bits/stdc++.h>

using namespace std;
#define int long long

struct point {
	int x, y;
	point() {
		x = y = 0;
	}
	point(int a, int b) {
		x = a, y = b;
	}
};

struct line {
	int a, b, c;
	line() {
		a = b = c = 0;
	}
	line(int x, int y, int z) {
		a = x, b = y, c = z;
	}
	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
		int g = __gcd(a, b);
		g = __gcd(g, c);
		a /= g;
		b /= g;
		c /= g;
	}
};

bool operator<(line a, line b) {
	if (a.a != b.a)
		return a.a < b.a;
	if (a.b != b.b)
		return a.b < b.b;
	return a.c < b.c; 
}

int n;
vector <point> help;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		point x;
		cin >> x.x >> x.y;
		help.push_back(x);
	}
}

bool cross(line l1, line l2) {
    return l1.b * l2.a - l2.b * l1.a != 0;
}


int ans = 0;

void run() {
	set <line> have;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			have.insert(line(help[i], help[j]));
		}
	}

//	cout << have.size() << endl;

	ans = (int)have.size() * ((int)have.size() - 1) / 2;
//	cout << ans << endl;
	map <pair <int, int>, int> aaa, bbb;
	
	for (auto i : have) {
		int x = i.a;
		int y = i.b;
		if (x < 0 && y < 0) {
			x *= -1;
			y *= -1;
		}
		bool flag = false;
		if (x < 0 || y < 0)
			flag = true;
		x = abs(x);
		y = abs(y);
		int g = __gcd(x, y);
		x /= g;
		y /= g;
		if (!flag || x == 0 || y == 0)
			aaa[{x, y}]++;
		else
			bbb[{x, y}]++;
	}

	/*cout << "have" << endl;
	for (auto i : have) {
		cout << i.a << " " << i.b << " " << i.c << endl;
	}

	cout << "aaa = " << endl;
	for (auto i: aaa)
		cout << i.first.first << " " << i.first.second << " " << i.second << endl;
	cout << "bbb = " << endl;
	for (auto i : bbb)
		cout << i.first.first << " " << i.first.second << " " << i.second << endl;
*/
	for (auto i : aaa)
		ans -= i.second * (i.second - 1) / 2;
	for (auto i : bbb)
		ans -= i.second * (i.second - 1) / 2;
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