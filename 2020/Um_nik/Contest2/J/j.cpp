#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct fraction{
	ll x, y;
	fraction() {
		x = 0, y = 1;
	}
	fraction(ll _x) {
		x = _x, y = 1;
	}
	fraction(ll _x, ll _y) {
		x = _x, y = _y;
		assert(y != 0);
		ll g = __gcd(abs(x), abs(y));
		assert(g != 0);
		x /= g;
		y /= g;
		if (y < 0) {
			x *= -1;
			y *= -1;
		}
		if (x == 0) {
			y = 1;
		}
	}
};

bool operator<(const fraction & a, const fraction & b) {
	return a.x * b.y < b.x * a.y;
}

bool operator==(const fraction & a, const fraction & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

bool operator!=(const fraction & a, const fraction & b) {
	return !(a == b);
}

fraction operator-(const fraction & a, const fraction & b) {
	return fraction(a.x * b.y - a.y * b.x, a.y * b.y); 
}

fraction operator+(const fraction & a, const fraction & b) {
	return fraction(a.x * b.y + a.y * b.x, a.y * b.y); 
}

fraction operator*(const fraction & a, const fraction & b) {
	return fraction(a.x * b.x, a.y * b.y);
}

fraction operator/(const fraction & a, const fraction & b) {
	assert(b.x != 0);
	return a * fraction(b.y, b.x);
}

struct point{
	fraction x, y;
	point() {
		x = fraction(), y = fraction();
	}
	point(fraction _x, fraction _y) {
		x = _x, y = _y;
	}
};

point operator+(const point & a, const point & b) {
	return point(a.x + b.x, a.y + b.y);
}

point operator-(const point & a, const point & b) {
	return point(a.x - b.x, a.y - b.y);
}

point operator/(const point & a, const int d) {
	return point(a.x / fraction(d), a.y / fraction(d));
}

point norm(point a) {
	if (a.x != fraction()) {
		a.y = a.y / a.x;
		a.x = fraction(1);
		return a;
	} else {
		return point(fraction(0), fraction(1));
	}
}

bool operator<(const point & a, const point & b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

bool operator==(const point & a, const point & b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

const int MAXN = 1e3 + 10;
int n;
point a[MAXN];

#define vec point

vector<point> haveCentr;
vector<vector<vec>> haveVec;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int p1, q1, p2, q2;
		cin >> p1 >> q1 >> p2 >> q2;
		fraction x(p1, q1), y(p2, q2);
		fraction nx = x / ((x * x) + (y * y));
		fraction ny = y / ((x * x) + (y * y));
		a[i] = point(nx, ny);
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			haveCentr.push_back(a[i] + a[j]);
		}
	}

	sort(all(haveCentr));
	haveCentr.resize(unique(all(haveCentr)) - haveCentr.begin());
	haveVec.resize(haveCentr.size());

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int pos = lower_bound(all(haveCentr), a[i] + a[j]) - haveCentr.begin();
			haveVec[pos].push_back(norm(a[i] - a[j]));
		}
	}
	for (int i = 0; i < (int)haveVec.size(); i++) {
		if ((int)haveVec.size() < 2) continue; 
		sort(all(haveVec[i]));
		int fans = 1;
		int cnt = 0;
		int sum = 0;
		for (int l = 0; l < (int)haveVec[i].size(); l++) {
			int r = l;
			while (r < (int)haveVec[i].size() && haveVec[i][l] == haveVec[i][r]) r++;
			fans = mul(fans, r - l + 1);
			cnt += r - l;
			l = r - 1;
		}
		fans = sub(fans, 1);
		fans = sub(fans, cnt);
		ans = add(ans, fans);
	}
	cout << ans << endl;
	return 0;
}
