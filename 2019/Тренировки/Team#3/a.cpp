#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int s, g;

void read() {
	cin >> s >> g;
}

void run() {
	if (s % g != 0) {
		cout << -1 << endl;
		exit(0);
	}
	s /= g;
	if (s < 2) {
		cout << -1 << endl;
		exit(0);
	}
	cout << g << " " << (s - 1) * g << endl;
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