#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct point{
	int x, y;
	string c;
	point() {}
	point(int a, int b) {
		x = a, y = b;
	}
	point(int a1, int b1, char c1) {
		x = a1, y = b1, c = "";
		c += c1;
	}
};

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

int operator^(const point & a, const point & b) {
	return a.x * b.y - a.y * b.x;
}

int operator*(const point & a, const point & b) {
	return a.x * b.x + a.y * b.y;
}

bool operator<(const point & a, const point & b) {
	return a.c < b.c;
}

bool check(int a, int b, int c, int d) {
	if (a > b) swap(a, b);
	if (c > d) swap(c, d);
	return max(a, c) <= min(b, d);
}

int sign(int x) {
	if (x == 0) return x;
	return abs(x) / x;
}

#define vec point

bool check(point a, point b, point c, point d) {
	if (!check(a.x, b.x, c.x, d.x)) return false;
	if (!check(a.y, b.y, c.y, d.y)) return false;
	vec v1 = b - a, v2 = c - a, v3 = d - a;
	if (sign(v1 ^ v2) * sign(v1 ^ v3) > 0) return false;
	v1 = d - c, v2 = a - c, v3 = b - c;
	if (sign(v1 ^ v2) * sign(v1 ^ v3) > 0) return false;
	return true;	
}

bool check(vector<point> & p, point last, point now) {
	vec v = now - last;
	if (v.x == 0 || v.y == 0) return false;
	if (abs(v.x) == abs(v.y)) return false;
	if (p.empty()) return true;
	vec v1 = p.back() - last;
	if (sign(v ^ v1) == 0 && sign(v * v1) > 0) return false;
	int n = p.size();
	for (int i = 0; i + 1 < n; i++) {
		if (check(p[i], p[i + 1], last, now))
			return false;
	}
	return true;
}

string solve(string a, vector<point> p, point last, set<point> need) {
	if (need.empty()) return a;
	auto x = need;
	for (auto i : x) {
		if (check(p, last, i)) {
			need.erase(i);
			p.push_back(last);
			string ans = solve(a + i.c, p, i, need);
			if (ans != "-1") return ans;
			p.pop_back();
			need.insert(i); 
		}
	}
	return "-1";
}

void solve(vector<string> table) {
	int n = 7, m = 7;
	point start;
	set<point> need;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '.') continue;
			if (table[i][j] == 's') {
				start = point(i, j, 's');
				continue;
			}
			need.insert(point(i, j, table[i][j]));
		}
	}

	string ans = solve("s", {}, start, need);
	if (ans == "-1")
		cout << "impossible!" << endl;
	else
		cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	while (true) {
		string s;
		cin >> s;
		if (s == "0") return 0;
		vector<string> table;
		table.push_back(s);
		for (int i = 0; i < 6; i++) {
			cin >> s;
			table.push_back(s);
		}
		solve(table);
	}
	return 0;
}