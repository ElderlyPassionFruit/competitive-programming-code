#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
}

int calc_even(int x) {
	return x / 2;
}


int calc_odd(int x, int a) {	
	return calc_even(x - a) + 1;
}



int ans;

void run() {
	ans = 1;
	if (n % 2 == 0) {
		ans = calc_even(n);
		return;
	}
	for(int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			chkmax(ans, calc_odd(n, i));
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