#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const ld EPS = 1e-8;

int sign(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0; 
}

struct pt{
	ld x, y;
	pt() {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

ld operator^(const pt & a, const pt & b) {
	return a.x * b.y - a.y * b.x;
}

bool operator<(const pt & a, const pt & b) {
	if (sign(a ^ b) == 0) {
		if (sign(a.x - b.x) == 0) {
			return sign(a.y - b.y) == -1;
		} else {
			return sign(a.x - b.x) == -1; 
		}
	} else {
		return sign(a ^ b) < 0;
	}
}

struct line{
	pt a;
	pt v;
	line() {}
	void read() {
		ld t1, t2;
		cin >> t1 >> a.x >> a.y >> t2 >> v.x >> v.y;
		v.x = (v.x - a.x) / (t2 - t1);
		v.y = (v.y - a.y) / (t2 - t1);
		a.x -= v.x * t1;
		a.y -= v.y * t1;
	}
};

const int MAXN = 1111;
int n;
int ans = 0;
line p[MAXN];
ld a[MAXN];
pt b[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		p[i].read();
	}
	for (int i = 0; i < n; i++) {
		int topQ = 0;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			line now;
			now.a.x = p[j].a.x - p[i].a.x;
			now.a.y = p[j].a.y - p[i].a.y;
			now.v.x = p[j].v.x - p[i].v.x;
			now.v.y = p[j].v.y - p[i].v.y;
			ld t = 0;
			if (sign(now.v.x)) {
				t = now.a.x / now.v.x;
			} else if (sign(now.v.y)) {
				t = now.a.y / now.v.y;
			}
			if (sign(now.a.x - now.v.x * t) == 0 && sign(now.a.y - now.v.y * t) == 0) {
				a[topQ] = t;
				b[topQ] = now.v;
				topQ++;
			}
		}
		if (!topQ) continue;
		ans = max(ans, 1);
		sort(a, a + topQ);
		int fans;
		fans = 1;
		for (int j = 1; j < topQ; j++) {
			if (sign(a[j] - a[j - 1]) != 0) {
				fans = 0;
			}
			fans++;
			ans = max(ans, fans);
		}
		sort(b, b + topQ);
		fans = 1;
		for (int j = 1; j < topQ; j++) {
			if (sign(b[j] ^ b[j - 1]) == 0) {
				if (sign(b[j].x - b[j - 1].x) != 0 || sign(b[j].y - b[j - 1].y) != 0) {
					fans++;
				}
			} else {
				fans = 1;
			}
			ans = max(ans, fans);
		}
	}
	cout << ans + 1 << endl;
	return 0;
}