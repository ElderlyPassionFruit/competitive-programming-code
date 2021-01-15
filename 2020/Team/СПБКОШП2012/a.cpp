#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

struct rect{
	int a, b;
	rect() {}
	rect(int x, int y) {
		a = x, b = y;
	}
};

int n, w, h;
vector<rect> have;

bool check(int i, ld k) {
	return have[i].a * k <= w && have[i].b * k <= h;
}

bool check(ld k) {
	for (int i = 0; i < n; i++)
		if (!check(i, k))
			return false;
	ld now_w = k * have[0].a;
	ld now_h = k * have[0].b;
	for (int i = 1; i < n; i++) {
		if (have[i].b != have[i - 1].b) {
			now_h += k * have[i].b;
			now_w = k * have[i].a;
		}
		else {
			if (now_w + k * have[i].a <= w) {
				now_w += k * have[i].a;
			}
			else {
				now_h += k * have[i].b;
				now_w = k * have[i].a;
			}
		}
	}
	return now_h <= h;
}

const ld EPS = 1e-9;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("advert.in", "r", stdin);
	freopen("advert.out", "w", stdout);
	cin >> n >> w >> h;
	have.resize(n);
	for (auto &i : have)
		cin >> i.a >> i.b;
	//cout << check(100) << endl;
	ld l = 0, r = 1e9 + 10;
	for (int i = 0; i < 60; i++) {
		ld mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	cout << l << endl;
	return 0;
}