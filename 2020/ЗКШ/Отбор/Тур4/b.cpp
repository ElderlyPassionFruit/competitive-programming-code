#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

//#define int ll

int x, y;
void read_x() {
	string s;
	cin >> s;
	if (s[0] == '1') {
		x = 1, y = 1;
		return;
	}
	assert(s.size() > 2);
	y = 1;
	for (int i = 2; i < s.size(); i++) {
		x *= 10;
		y *= 10;
		x += s[i] - '0';	
	}
}

int n;

void read() {
	read_x();
	cin >> n;
}

vector<int> get_primes(int n) {
	vector<int> ans;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n > 1)
		ans.push_back(n);
	return ans;
}

bool check(int mid, int n) {
	return (ll)mid * y <= (ll)n * x;
}

int get_x(int n) {
	int l = 0, r = n;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid, n))
			l = mid;
		else
			r = mid;
	}
	return l;
}

int get(int n) {
	int ans = 0;
	int x = get_x(n);
	vector<int> p = get_primes(n);
	for (int i = 1; i <= x; i++) {
		bool flag = true;
		for (auto j : p) {
			if (i % j == 0) flag = false;
		}
		if (flag)
			ans++;
	}
	return ans;
} 

int ans;

void run() {
	ans = 0;
	for (int i = 2; i <= n; i++) {
		ans += get(i);
		//cout << "i = " << i << " get = " <<  get(i) << " x = " << get_x(i) << endl; 
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