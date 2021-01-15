#include <bits/stdc++.h>

using namespace std;
#define int long long
int r1, s1, p1;
int r2, s2, p2;
void read() {
	cin >> r1 >> s1 >> p1 >> r2 >> s2 >> p2;
}
int ans;
void run() {
	ans = 0;
	int x = min(r1, s2); 
	ans += x;
	r1 -= x;
	s2 -= x;
	x = min(s1, p2);
	ans += x;
	x = min(p1, r2);
	ans += x;
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("rps.in", "r", stdin);
	freopen("rps.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}