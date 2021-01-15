#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
int d;
vector<int> a;
void read() {
	a.resize(3);
	for (auto &i : a)
		cin >> i;
	cin >> d;
	sort(a.begin(), a.end());
	int ans = 0;
	ans += max(d - abs(a[1] - a[0]), 0LL);
	ans += max(d - abs(a[2] - a[1]), 0LL);
	cout << ans << endl;
}

void run() {

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