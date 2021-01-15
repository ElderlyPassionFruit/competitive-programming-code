#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll
int n;

void read() {
	cin >> n;
}

vector<int> factor(int x) {
	vector<int> p;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			p.push_back(i);
			p.push_back(x / i);
		}
	}
	sort(all(p));
	p.resize(unique(all(p)) - p.begin());
	return p;
}

bool check(int x) {
	// /cout << x << endl;
	int N = n;
	if (x < 2 || x > N) return false;
	while (N % x == 0) {
		N /= x;
	}
	if (N == 1) return true;
	if (N < x) return false;
	if ((N - 1) % x == 0) return true;
	return false;
}

int ans;

void run() {
	auto fans = factor(n);
	ans = 0;
	for (auto i : fans) {
		ans += check(i);
		//cout << i << " " << check(i) << endl;
	}
	fans = factor(n - 1);
	for (auto i : fans) {
		ans += check(i);
		//cout << i << " " << check(i) << endl; 
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