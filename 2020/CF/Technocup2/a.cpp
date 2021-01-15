#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, p;

void read() {
	cin >> n >> p;
}

int ans = -1;

int get(int x) {
	int ans = 0;
	while (x) {
		ans += x % 2;
		x /= 2;
	}	
	return ans;
}

int run() {
	for (int i = 1; i < 40; i++) {
		if (n - p * i > 0 && get(n - p * i) <= i) {
			return i;
		}
	}
	return -1;
}

int run2() {
	for (int i = 1; i < 20000; i++) {
		if (n - p * i >= i && get(n - p * i) <= i)
			return i;
	}
	return -1;
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for (int i = 1; i <= 10000000; i++) {
		n = rand() % (int)(1e9);
		p = rand() % (2000) - 1000;
		if (run() != run2()) {
			cout << "WA " << i << endl;
			cout << n << " " << p << endl;
			cout << run() << " " << run2() << endl;
			break; 
		}
		cout << "OK " << i << endl;
	}
	//read();
	//run();
	//write();
	return 0;
}