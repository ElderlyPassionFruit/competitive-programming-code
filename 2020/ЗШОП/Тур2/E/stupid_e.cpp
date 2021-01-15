#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string a, b;

void read() {
	cin >> a >> b;
}

const int MAXA = 4;

bool check(int mask) {
	vector<char> fa, fb;
	for (auto i : a) {
		if ((mask >> (i - 'a')) & 1) continue;
		fa.push_back(i);
	}
	for (auto i : b) {
		if ((mask >> (i - 'a')) & 1) continue;
		fb.push_back(i);
	}
	/*cout << mask << endl;
	for (auto i : fa)
	cout << i << " ";
	cout << endl;
	for (auto i : fb)
	cout << i << " ";
	cout << endl; */
	return fa == fb;
}

int get(int mask) {
	int ans = 0;
	while (mask) {
		ans += mask % 2;
		mask /= 2;
	}
	return ans;
}

int ans;

void run() {
	ans = MAXA;
	for (int i = 0; i < (1 << MAXA); i++) {
		if (check(i)) {
			chkmin(ans, get(i));
		}
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