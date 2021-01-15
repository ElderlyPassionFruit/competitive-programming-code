#include <bits/stdc++.h>

using namespace std;
#define int long long

struct rect{
	int l, r, u, d;
	rect() {
		l = 0, r = 0, u = 0, d = 0;
	}
	rect(int a, int b, int c, int d1) {
		l = a, r = b, u = c, d = d1;
	}
};

vector<rect> a;
int n;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.l >> i.d >> i.r >> i.u;
	}
}

set<int> lr, ud;
map <int, int> c1, c2;
void run() {
	for (auto i : a) {
		lr.insert(i.l);
		lr.insert(i.r);
		ud.insert(i.u);
		ud.insert(i.d);
	}
	int cnt1 = 0;
	for (auto i: lr)
		c1[i] = cnt1++;
	int cnt2 = 0;
	for (auto i : ud)
		c2[i] = cnt2++;
}

void write() {
	cout << n << endl;
	for (auto i : a) {
		cout << c1[i.l] << " " << c2[i.d] << " " << c1[i.r] << " " << c2[i.u] << endl;
	}
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