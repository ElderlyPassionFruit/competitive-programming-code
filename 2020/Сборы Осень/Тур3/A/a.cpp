#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment{
	int l, r;
	segment() {}
	segment(int a, int b) {
		l = a, r = b;
	}
};

int n, k, c, d;
vector<segment> a;

bool operator<(const segment & a, const segment & b) {
	return a.r - a.l < b.r - b.l;
}


void read() {
	cin >> n >> k >> c >> d;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.l >> i.r;
	}
}

int ans = 1e18;

void recalc(int cnt, int len) {
	chkmin(ans, (cnt + k - 1) / k * c + len * d);
}

void run() {
	vector<segment> have;
	for (int i = 1; i < n; i++) {
		have.push_back({a[i - 1].r, a[i].l});
	}
	sort(all(have));
	int len = 0;
	for (auto i : a){
		len += i.r - i.l;
	}

	int cnt = n - k;
	recalc(cnt, len);

	for (auto i : have) {
		len += i.r - i.l;
		cnt--;
		recalc(cnt, len);
	}
}

void write() {
	cout << ans << endl;
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