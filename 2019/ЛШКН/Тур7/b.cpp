#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, s;
void read() {
	cin >> n >> s;
}

int ans;

bool check(int x, int s) {
	int sum = 0;
	int y = x;
	while (y) {
		sum += y % 10;
		y /= 10;
	}
	return x - sum >= s;
}

void run() {
	int ok = s + 200;
	ans += max(0LL, n - ok + 1);
	//cout << ans << endl;
	for (int i = s; i < min(ok, n + 1); i++) {
		//cout << "i = " << i << " check = " << check(i, s) << endl;
		ans += check(i, s);
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