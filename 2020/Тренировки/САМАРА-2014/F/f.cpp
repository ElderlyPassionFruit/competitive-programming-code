#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

int q, n;
vector<pt> a;
int AmxX, AmxY;
void make(vector<pt> & a, int & mxX, int & mxY) {
	int mnX = min_element(all(a), [&] (pt i, pt j) {return i.x < j.x;})->x;
	int mnY = min_element(all(a), [&] (pt i, pt j) {return i.y < j.y;})->y;
	for (auto &i : a) {
		i.x -= mnX;
		i.y -= mnY;
	}
	mxX = max_element(all(a), [&] (pt i, pt j) {return i.x < j.x;})->x;
	mxY = max_element(all(a), [&] (pt i, pt j) {return i.y < j.y;})->y;
	sort(all(a), [&] (pt i, pt j) {return tie(i.x, i.y) < tie(j.x, j.y);});
}

void read() {
	cin >> q >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
	make(a, AmxX, AmxY);
	/*cout << "a = " << endl;
	for (auto &i : a) {
		cout << i.x << " " << i.y << endl;
	}
	cout << AmxX << " " << AmxY << endl;*/
}

bool check(int x1, int x2, int A, int B) {
	return (ll) x1 * B == (ll) x2 * A;
}

void solve() {
	vector<pt> have(n);
	for (auto &i : have) {
		cin >> i.x >> i.y;
	}
	int MYmxX, MYmxY;
	make(have, MYmxX, MYmxY);
	for (int i = 0; i < n; i++) {
		if (!check(a[i].x, have[i].x, AmxX, MYmxX)) {
			cout << "NO\n";
			return;
		}
		if (!check(a[i].y, have[i].y, AmxY, MYmxY)) {
			cout << "NO\n";
			return;
		}
	}
	if (!check(MYmxX, MYmxY, AmxX, AmxY)) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	read();
	while (q--) {
		solve();
	}
	return 0;
}