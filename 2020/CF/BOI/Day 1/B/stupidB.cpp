#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}
#define int ll

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int gcd(int a, int b, int c) {
	return gcd(a, gcd(b, c));
}

struct point{
	int x, y, z;
	point() {}
	void norm() {
		int g = gcd(abs(x), abs(y), abs(z));
		assert(g != 0);
		x = x / g;
		y = y / g;
		z = z / g;
		/*if (x < 0) {
			x = -x, y = -y, z = -z;
		} else if (x == 0 && y < 0) {
			y = -y, z = -z;
		} else if (x == 0 && y == 0 && z < 0) {
			z = -z;
		}*/
	}
	point(int _x, int _y, int _z) {
		x = _x, y = _y, z = _z;
		norm();
	}
	void wr() {
		cout << "x = " << x << " y = " << y << " z = " << z << endl;
	}
};

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y, a.z) < tie(b.x, b.y, b.z);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y, a.z) == tie(b.x, b.y, b.z);
}

point getPlane(point x, point y) {
	int a, b, c;
	a = x.y * y.z - x.z * y.y;
	b = x.z * y.x - x.x * y.z;
	c = x.x * y.y - x.y * y.x;
	return point(a, b, c);
}

int getDet(vector<vector<int>> a) {
	return a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[1][0] * a[2][1] * a[0][2] - a[2][0] * a[1][1] * a[0][2] - a[0][1] * a[1][0] * a[2][2] - a[2][1] * a[1][2] * a[0][0];
}

bool checkBasis(point a, point b, point c) {
	return getDet({
		{a.x, b.x, c.x},
		{a.y, b.y, c.y},
		{a.z, b.z, c.z}
	}) != 0;
}

point need;

map<point, int> have;

void add(point a) {
	have[a]++;
}

void del(point a) {
	have[a]--;
}

bool checkAns1() {
	/*cout << "have = " << endl;
	for (auto i : have) {
		point a = i.first;
		a.wr();
		cout << i.second << endl;
	}
	cout << endl;*/
	return have[need] > 0;
}

bool checkAns2() {
	//return false;
	/*set<point> now;
	for (auto i : have) {
		if (i.second == 0) continue;
		point fadd = getPlane(need, i.first);
		if (now.count(fadd)) return true;
		now.insert(fadd);
	}
	return false;*/
	vector<point> now;
	for (auto i : have) {
		if (i.second == 0) continue;
		now.push_back(i.first);
	}
	for (int i = 0; i < (int)now.size(); i++) {
		for (int j = i + 1; j < (int)now.size(); j++) {
			if (checkBasis(now[i], now[j], need)) continue;
			return true;
		}
	}
	return false;
}

bool checkAns3() {
	//return false;
	//if (have.size() < 3) return false;
	/*set<point> now;
	for (auto i : have) {
		if (i.second == 0) continue;
		for (auto j : have) {
			if (j.second == 0) continue;
			if (i.first == j.first) continue;
			now.insert(getPlane(i.first, j.first));
			if (now.size() == 2) return true;
		}
	}
	return false;*/
	vector<point> now;
	for (auto i : have) {
		if (i.second == 0) continue;
		now.push_back(i.first);
	}
	for (int i = 0; i < (int)now.size(); i++) {
		for (int j = i + 1; j < (int)now.size(); j++) {
			for (int k = j + 1; k < (int)now.size(); k++) {
				if (checkBasis(now[i], now[j], now[k])) {
					return true;
				}
			}
		}
	}
	return false;
}

int getAns() {
	if (checkAns1()) return 1;
	if (checkAns2()) return 2;
	if (checkAns3()) return 3;
	return 0;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	cin >> need.x >> need.y >> need.z;
	need.norm();
	//need.wr();
	int q;
	cin >> q;
	vector<point> have;
	vector<bool> used(q, false);
	while (q--) {
		char type;
		cin >> type;
		if (type == 'A') {
			point a;
			cin >> a.x >> a.y >> a.z;
			a.norm();
			//a.wr();
			have.push_back(a);
			add(a);
		} else if (type == 'R') {
			int ind;
			cin >> ind;
			ind--;
			assert(!used[ind]);
			assert(ind < have.size());
			del(have[ind]);
		}
		cout << getAns() << "\n";
	}
	return 0;
}