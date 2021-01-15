#include <bits/stdc++.h>

using namespace std;
#define int long long

struct point{
	int x, y;
	point() {
		x = 0;
		y = 0;
	}
	point(int a, int b) {
		x = a;
		y = b;
	}
};

point operator-(point a, point b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(point a, point b) {
	return a.x * b.y - a.y * b.x;
}

point p0;

bool cmp(const pair <point, int> & a, const pair <point, int> & b) {
	point x = a.first - p0;
	point y = b.first - p0;
	return (x ^ y) > 0;
}

#define vec point

vector <pair <point, int> > convex_hull(vector <pair <point, int> > g) {
	int n = g.size();
	for (int i = 0; i < n; i++) {
		if (g[i].first.y < g[0].first.y || (g[i].first.y == g[0].first.y && g[i].first.x < g[0].first.x))
			swap(g[0], g[i]);
	}
	p0 = g[0].first;
	sort(g.begin() + 1, g.end(), cmp);
	vector <pair <point, int> > hull;
	hull.push_back(g[0]);
	g.push_back(g[0]);
	for (int i = 1; i <= n; i++) {
		while (hull.size() >= 2) {
			int last = hull.size() - 1;
			vec v1 = hull[last].first - hull[last - 1].first;
			vec v2 = g[i].first - hull[last].first;
			if ((v1 ^ v2) > 0) {
				break;
			}
			hull.pop_back();
		}
		hull.push_back(g[i]);
	}
	hull.pop_back();
	return hull;
} 

int n;
vector <pair <point, int> > p;
void read() {
	cin >> n;
	p.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i].first.x >> p[i].first.y;
		p[i].second = i + 1;
 	}
}

bool get_ans(const vector <pair <point, int> > &a) {
	cout << "? ";
	cout << a.size() << " ";
	for (auto i : a) {
		cout << i.second << " ";
	}
	cout << endl;
	string ans;
	cin >> ans;
	return ans == "Yes";
}

void fans(const vector <pair <point, int> > &a) {
	cout << "! ";
	cout << a.size() << " ";
	for (auto i : a) {
		cout << i.second << " ";
	}
	cout << endl;
}

bool check(point a, point b, point c, point x) {
	int a1 = (b - a) ^ (b - x);
	int a2 = (c - b) ^ (c - x);
	int a3 = (a - c) ^ (a - x);
	return (a1 < 0 && a2 < 0 && a3 < 0) || (a1 > 0 && a2 > 0 && a3 > 0);
}

vector <vector <int> > help;
void make() {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				bool flag = false;
				for (int x = 0; x < n; x++) {
					if (x == i || x == j || x == k)
						continue;
					if (check(p[i].first, p[j].first, p[k].first, p[x].first)) {
						flag = true;
						break;
					}
				}
				if (flag)
					continue;
				help.push_back({i + 1, j + 1, k + 1});
			}
		}
	}
}

bool operator==(point a, point b) {
	return (a.x == b.x) && (a.y == b.y);
}

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

void test() {
	vector <pair <point, int> > g = p;
	vector <bool> used(p.size() + 10, false);
	while (g.size() > 3) {
		auto hull = convex_hull(g);
		if (hull.size() == 3) {
			for (int i = 0; i < hull.size(); i++) {
           		if (used[hull[i].second] == true)
            	    continue;
          	  	pair <point, int> mid = hull[i];
            	vector <pair <point, int> > fhelp;
            	for (int j = 0; j < help.size(); j++) {
                	if (help[j] == mid) continue;
                	fhelp.push_back(help[j]);
            	}
            	vector <pair <point, int> > fhelp_hull = convex_hull(fhelp);
            	if (get_ans(fhelp_hull)) {
                	help = fhelp;
                	break;
            	}
            	used[hull[i].second] = true;
      	 	}
		}
		else {
		}
	}
	fans(help);
}

void run() {
	int m;
	cin >> m;
	while (m--) {
		test();
	}
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