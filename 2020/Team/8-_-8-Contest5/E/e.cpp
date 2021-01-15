#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
struct Point{
	int x, y;
	Point() {}
	Point(int _x, int _y) {
		x = _x, y = _y;
	}
};

Point operator-(const Point & a, const Point & b) {
	return Point(a.x - b.x, a.y - b.y);
}

bool operator<(const Point & a, const Point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const Point & a, const Point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

void make(vector<Point> & a) {
	Point x = *min_element(all(a));
	for (auto &i : a) {
		i = i - x;
	}
	sort(all(a));
}

bool check(vector<Point> a, vector<Point> b) {
	make(a);
	make(b);
	return a == b;
}

void turn(int it, vector<Point> & a) {
	if (it == 0) {
		for (auto &[x, y] : a) {
			x = -x;
		}
	} else if (it == 1) {
		for (auto &[x, y] : a) {
			y = -y;
		}
	} else if (it == 2) {
		for (auto &[x, y] : a) {
			swap(x, y);
		}
	} else {
		for (auto &[x, y] : a) {
			swap(x, y);
			x = -x;
		}
	}
}

signed main() {
	freopen("fields.in", "r", stdin);
	freopen("fields.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<Point> a(n), b(n);
	for (auto &[x, y] : a) {
		cin >> x >> y;
	}
	for (auto &[x, y] : b) {
		cin >> x >> y;
	}
	for (int it1 = 0; it1 < 2; it1++) {
		for (int it2 = 0; it2 < 2; it2++) {
			for (int it3 = 0; it3 < 2; it3++) {
				for (int it4 = 0; it4 < 2; it4++) {
					if (check(a, b)) {
						cout << "YES\n";
						exit(0);
					}
					turn(3, a);
				}
				turn(2, a);
			}
			turn(1, a);
		}
		turn(0, a);
	}
	cout << "NO\n";
	return 0;
}