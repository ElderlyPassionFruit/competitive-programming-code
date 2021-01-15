#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, h;

void read() {
	cin >> n >> h;
}

const int INF = 1e18;

int ans;

void run() {
	int now = 0;
	int minh = 0, maxh = 0;
	for (int i = 0; i < n; i++) {
		char type;
		int x;
		cin >> type;
		cin >> x;
		if (type == 'u')
			now += x;
		else
			now -= x;
		chkmin(minh, now);
		chkmax(maxh, now);
	}
	//cout << minh << " " << maxh << endl; 
	if (maxh - minh >= h) {
		ans = 0;
	}
	else {
		ans = maxh - minh;
		ans = h - ans;
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