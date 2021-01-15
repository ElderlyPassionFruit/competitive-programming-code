#include <bits/stdc++.h>

using namespace std;
struct point {
	int x, y;
	point() {
		x = 0, y = 0;
	}
	point(int a, int b) {
		x = a, y = b;
	}
};


struct line {
	int a, b, c;
	line() {
		a = 0, b = 0, c = 0;
	}

	line(point x, point y) {
		a = y.y - x.y;
		b = x.x - y.x;
		c = x.y * y.x - x.x * y.y;
	}
};

double eval(line l, int x) {
	return (double) (-l.a * x - l.c) / l.b;
}

int n;

vector<pair <point, point>> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.first.x >> i.first.y >> i.second.x >> i.second.y;
		if (i.first.x > i.second.x) {
			swap(i.first, i.second);
		}
		if (i.first.x == i.second.x && i.first.y > i.second.y) {
			swap(i.first, i.second);
		}
	}
}

bool help_check1(pair <point, point> a, pair <point, point> b) {
	return a.first.x == a.second.x && b.first.x == b.second.x;
}

bool check1(pair <point, point> a, pair <point, point> b) {
	return a.first.x == a.second.x && a.first.x == b.first.x && a.first.x == b.second.x && a.first.y < b.first.y;
}

bool help_check2(pair <point, point> a, pair <point, point> b) {
	return a.first.x == a.second.x && (b.first.x <= a.first.x && b.second.x >= a.first.x);
}

bool check2(pair <point, point> a, pair <point, point> b) {
	line help(b.first, b.second);
	return eval(help, a.first.x) > a.second.y;
}

bool help_check3(pair <point, point> a, point x) {
	return a.first.x <= x.x && a.second.x >= x.x;
}

bool check3(pair <point, point> a, point x) {
	line help(a.first, a.second);
	return eval(help, x.x) < x.y;
}

bool check(pair <point, point> a, pair <point, point> b) {
	if (help_check1(a, b)) return check1(a, b);
	if (help_check2(a, b)) return check2(a, b);
	if (help_check3(a, b.first)) return check3(a, b.first);
	if (help_check3(a, b.second)) return check3(a, b.second);
	if (help_check3(b, a.first)) return !check3(b, a.first);
	if (help_check3(b, a.second)) return !check3(b, a.second);
	return false;
}

vector<vector<int> > gr;
vector<int> g;
void run() {
	g.resize(n);
	gr.resize(n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (check(a[j], a[i])){
				g[i]++;
				gr[j].push_back(i);
			}
			if (check(a[i], a[j])) {
				g[j]++;
				gr[i].push_back(j);
			}
		}
	}

	vector<bool> used(n, false);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[j] == 0 && !used[j]) {
				used[j] = true;
				cout << j + 1 << " ";
				for (auto k : gr[j]) {
					g[k]--;
				}
			}
		}
	}
	cout << endl;
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