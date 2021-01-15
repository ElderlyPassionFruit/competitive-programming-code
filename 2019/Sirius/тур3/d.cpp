#include <bits/stdc++.h>

using namespace std;
#define int long long
struct point{
	int x, y;
	point () {
		x = y = 0;
	}
	point (int a, int b) {
		x = a, y = b;
	}
};

struct segment{
	point a, b;
	segment() {
		a = point();
		b = point();
	}
	segment(point x, point y) {
		a = x, b = y;
	}
};

const int MAXN = 1e5 + 10;
point p[MAXN];
vector<segment> h, w;

int n;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
	}

	for (int i = 0; i < n; i++) {
		point a = p[i];
		point b = p[(i + 1) % n];
		if (a.x == b.x) {
			h.push_back({a, b});
		}
		else {
			w.push_back({a, b});
		}
	}
}

bool check1(int H) {
	int ar1 = 0, ar2 = 0;
	for (auto i : w) {
		int ar = (H - i.a.y) * abs(i.a.x - i.b.x);
		if (ar > 0)
			ar1 += abs(ar);
		else
			ar2 += abs(ar);
	}
	return ar1 < ar2;
}

bool check1_fans(int H) {
	int ar1 = 0, ar2 = 0;
	for (auto i : w) {
		int ar = (H - i.a.y) * abs(i.a.x - i.b.x);
		if (ar > 0)
			ar1 += abs(ar);
		else
			ar2 += abs(ar);
	}
	return ar1 == ar2;
}


bool check2(int W) {
	int ar1 = 0, ar2 = 0;
	for (auto i : h) {
		int ar = (W - i.a.x) * abs(i.a.y - i.b.y);
		if (ar > 0)
			ar1 += abs(ar);
		else
			ar2 += abs(ar);
	}
	return ar1 < ar2;
}

bool check2_fans(int W) {
	int ar1 = 0, ar2 = 0;
	for (auto i : h) {
		int ar = (W - i.a.x) * abs(i.a.y - i.b.y);
		if (ar > 0)
			ar1 += abs(ar);
		else
			ar2 += abs(ar);
	}
	return ar1 == ar2;
}

int sq(int x) {
	return x * x;
}

double dist(point a, point b) {
	return sqrt(sq(a.x - b.x) + sq(a.y - b.y)); 
}

void run() {
	int l = 0, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check1(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	} 
	cout << endl;
	if (check1_fans(r)) {
		set <int> a;
		for (auto i : h) {
			int mid = r;
			if ((i.a.y >= mid && i.b.y <= mid) || (i.a.y <= mid && i.b.y >= mid)) {
				if (a.find(i.a.x) == a.end()) {
					a.insert(i.a.x);
				}
			} 
		}
		for (auto i : a) {
			for (auto j : a) {
				if (h.find({{i, r}, {j, r}}) == h.end() && h.find({{j, r}, {i, r}}) == h.end()) 
					cout << i << " " << r << " " << j << " " << r << endl;
			}
		}
		exit(0);
	}

	l = 0, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check2(mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	} 

	if (check2_fans(r)) {
		set <int> a;
		for (auto i : w) {
			int mid = r;
			if ((i.a.x >= mid && i.b.x <= mid) || (i.a.x <= mid && i.b.x >= mid)) {
				if (a.find(i.a.y) == a.end()) {
					a.insert(i.a.y);
				}
			} 
		}
		for (auto i : a) {
			for (auto j : a) {
				if (w.find({{r, i}, {r, j}}) == w.end() && w.find({{r, j}, {r, i}}) == w.end()) 
					cout << i << " " << r << " " << j << " " << r << endl;
			}
		}
		exit(0);
	}
	cout << "NO" << endl;
}

void write() {

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